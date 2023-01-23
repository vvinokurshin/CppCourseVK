#include "PostgreDataBase.h"

#include <iostream>

PostgreConnectParams::PostgreConnectParams(const std::string& dbName, const std::string& user,
                                           const std::string& password, const std::string& host,
                                           const std::string& port)
    : dbName(dbName), user(user), password(password), host(host), port(port) {
}

std::string PostgreConnectParams::paramsToString() const {
    std::string strParams = "dbname = " + dbName + " ";
    strParams += "user = " + user + " ";

    if (!password.empty()) {
        strParams += "password = " + password + " ";
    }

    if (!host.empty()) {
        strParams += "host = " + host + " ";
    }

    if (!port.empty()) {
        strParams += "port = " + port + " ";
    }

    std::cout << strParams;
    return strParams;
}

PostgreDataBase::PostgreDataBase(std::shared_ptr<PostgreConnectParams> conParams): connectParams(conParams) {
    con = std::make_shared<pqxx::connection>(connectParams->paramsToString());

    if ((*con).is_open()) {
        std::cout << "Opened database successfully: " << (*con).dbname() << std::endl;
    } else {
        std::cout << "Can't open database" << std::endl;
    }
}

json PostgreDataBase::select(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string query = "SELECT ";

    for (size_t i = 0; i < request["SELECT"].size(); ++i) {
        query += request["SELECT"][i].get<std::string>();

        if (i != request["SELECT"].size() - 1) {
            query += ", ";
        }
    }

    query += " FROM ";

    for (size_t i = 0, j = 0; i < request["FROM"].size(); ++i) {
        query += request["FROM"][i].get<std::string>();

        if (i > 0) {
            query += " ON " + request["JOIN ON"][j++].get<std::string>();
        }

        if (i != request["FROM"].size() - 1) {
            query += " JOIN ";
        }
    }

    if (request["WHERE"].size()) {
        query += " WHERE ";
    }

    for (size_t i = 0; i < request["WHERE"].size(); ++i) {
        query += request["WHERE"][i]["field"].get<std::string>() + "=";
        auto cur = request["WHERE"][i]["value"];
        std::string value;

        if (cur.is_string()) {
            value = "\'" + con->esc(cur.get<std::string>()) + "\'";
        } else if (cur.is_boolean()) {
            if (cur.get<bool>()) {
                value = "true";
            } else {
                value = "false";
            }
        } else {
            value = std::to_string(cur.get<int>());
        }

        query += value;

        if (i != request["WHERE"].size() - 1) {
            query += " AND ";
        }
    }

    try {
        pqxx::work worker(*con);
        pqxx::result result = worker.exec(query);
        worker.commit();
        response["result"] = {};

        for (pqxx::result::const_iterator row = result.begin(); row < result.end(); row++) {
            json cur = {};
            size_t i = 0;

            for (pqxx::row::const_iterator field = row->begin(); field != row->end(); ++field) {
                size_t type = result.column_type(i);

                if (type == 23) {
                    cur[result.column_name(i++)] = field.as<int>();
                } else if (type == 16) {
                    cur[result.column_name(i++)] = field.as<bool>();
                } else {
                    cur[result.column_name(i++)] = field.c_str();
                }
            }

            response["result"].push_back(cur);
        }
    } catch (std::exception& e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json PostgreDataBase::insert(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};

    std::string query = "INSERT INTO " + request["INTO"].get<std::string>() + "(";

    for (size_t i = 0; i < request["columns"].size(); ++i) {
        query += request["columns"][i].get<std::string>();

        if (i != request["columns"].size() - 1) {
            query += ", ";
        }
    }

    query += ") VALUES (";

    for (size_t i = 0; i < request["VALUES"].size(); ++i) {
        auto cur = request["VALUES"][i];
        std::string value;

        if (cur.is_null()) {
            value = "NULL";
        } else if (cur.is_string()) {
            value = "\'" + con->esc(cur.get<std::string>()) + "\'";
        } else if (cur.is_boolean()) {
            if (cur.get<bool>()) {
                value = "true";
            } else {
                value = "false";
            }
        } else {
            value = std::to_string(cur.get<int>());
        }

        query += value;

        if (i != request["VALUES"].size() - 1) {
            query += ", ";
        }
    }

    query += ")";

    try {
        pqxx::work worker(*con);
        pqxx::result result = worker.exec(query);

        query = "SELECT currval(\'" + request["INTO"].get<std::string>() + "_id_seq\')";
        result = worker.exec(query);
        worker.commit();

        json res = {};
        response["result"] = result.begin()->begin().as<int>();
    } catch (std::exception& e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json PostgreDataBase::remove(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};

    std::string query = "DELETE FROM " + request["FROM"].get<std::string>() + " WHERE ";

    for (size_t i = 0; i < request["WHERE"].size(); ++i) {
        query += request["WHERE"][i]["field"].get<std::string>() + "=";
        auto cur = request["WHERE"][i]["value"];
        std::string value;

        if (cur.is_string()) {
            value = "\'" + con->esc(cur.get<std::string>()) + "\'";
        } else if (cur.is_boolean()) {
            if (cur.get<bool>()) {
                value = "true";
            } else {
                value = "false";
            }
        } else {
            value = std::to_string(cur.get<int>());
        }

        query += value;

        if (i != request["WHERE"].size() - 1) {
            query += " AND ";
        }
    }

    try {
        pqxx::work worker(*con);
        pqxx::result result = worker.exec(query);
        worker.commit();
    } catch (std::exception& e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json PostgreDataBase::update(json request) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};

    std::string query = "UPDATE " + request["table"].get<std::string>() + " SET ";

    for (json::const_iterator it = request["SET"].begin(); it != request["SET"].end(); ++it) {
        query += it.key() + "=";

        if (it->is_null()) {
            query += "NULL";
        } else if (it->is_string()) {
            query += "\'" + con->esc(it->get<std::string>()) + "\'";
        } else {
            query += std::to_string(it->get<int>());
        }
        
        if (it != std::prev(request["SET"].end())) {
            query += ", ";
        }
    }

    query += " WHERE ";

    for (size_t i = 0; i < request["WHERE"].size(); ++i) {
                query += request["WHERE"][i]["field"].get<std::string>() + "=";
        auto cur = request["WHERE"][i]["value"];
        std::string value;

        if (cur.is_string()) {
            value = "\'" + con->esc(cur.get<std::string>()) + "\'";
        } else if (cur.is_boolean()) {
            if (cur.get<bool>()) {
                value = "true";
            } else {
                value = "false";
            }
        } else {
            value = std::to_string(cur.get<int>());
        }

        query += value;

        if (i != request["WHERE"].size() - 1) {
            query += " AND ";
        }
    }

    try {
        pqxx::work worker(*con);
        pqxx::result result = worker.exec(query);
        worker.commit();
    } catch (std::exception& e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
