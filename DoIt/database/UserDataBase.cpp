#include <iostream>

#include "UserDataBase.h"
#include "allDataBasesInfo.h"

UserDataBase::UserDataBase(std::shared_ptr<DataBase> cl): client(cl) {
}

json UserDataBase::getUsers() const {
    json request = {{"SELECT", {"*"}},
                    {"FROM", {userTableName}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && !response["result"].size()) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Validation failed"}};
    }

    return response;
}

json UserDataBase::addUser(const json& info) const {
    json request = {{"INTO", userTableName},
                    {"columns", {"username", "email", "password", "avatar"}},
                    {"VALUES", {info["username"], info["email"], info["password"], info["avatar"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getUserInfo(response["result"]);
    }

    return response;
}

json UserDataBase::removeUser(const size_t id) const {
    if (!checkUserExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "User doesn't exist"}};
    }

    json request = {{"FROM", userTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

json UserDataBase::checkUserValidation(const json& info) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {userTableName}},
                    {"JOIN ON", {}},
                    {"WHERE",
                     {{{"field", "username"}, {"value", info["username"].get<std::string>()}},
                      {{"field", "password"}, {"value", info["password"].get<std::string>()}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && !response["result"].size()) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Validation failed"}};
    }

    return response;
}

bool UserDataBase::checkUserExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {userTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}

json UserDataBase::updateUser(const json& info) const {
    size_t id = info["id"];

    if (!checkUserExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "User doesn't exist"}};
    }

    json request = {{"table", userTableName},
                    {"SET", info["info"]},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getUserInfo(id);
    }

    return response;
}

json UserDataBase::getUserInfo(const size_t id) const {
    json request = {{"SELECT", {"*"}},
                    {"FROM", {userTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "User doesn't exist"}};
    }

    return response;
}

json UserDataBase::getUserBoards(const size_t id) const {
    if (!checkUserExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "User doesn't exist"}};
    }

    json request = {
        {"SELECT", {"user_id", "board_id", "name", "caption", "background"}},
        {"FROM", {users2boardsTableName, boardTableName}},
        {"JOIN ON", {users2boardsTableName + ".board_id=" + boardTableName + ".id"}},
        {"WHERE", {{{"field", users2boardsTableName + ".user_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        response["result"] = json::array({});
        return response;
    }

    return response;
}
