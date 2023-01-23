#include <iostream>

#include "BoardDataBase.h"
#include "allDataBasesInfo.h"

BoardDataBase::BoardDataBase(std::shared_ptr<DataBase> cl): client(cl) {
}

json BoardDataBase::addBoard(const json& info) const {
    json request = {{"INTO", boardTableName},
                    {"columns", {"name", "caption", "background"}},
                    {"VALUES", {info["name"], info["caption"], info["background"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        json nested_request = {{"INTO", users2boardsTableName},
                               {"columns", users2boardsTableColumns},
                               {"VALUES", {info["user_id"], response["result"]}}};
        json nested_response = client->insert(nested_request);

        if (response[STATUS_FIELD] == SUCCESS_STATUS) {
            return getBoardInfo(response["result"]);
        }

        return nested_response;
    }

    return response;
}

json BoardDataBase::removeBoard(const size_t id) const {
    if (!checkBoardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {{"FROM", boardTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

json BoardDataBase::removeColumn(const size_t id) const {
    if (!checkColumnExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Column doesn't exist"}};
    }

    json request = {{"FROM", columnsTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

bool BoardDataBase::checkBoardExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {boardTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}


bool BoardDataBase::checkColumnExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {columnsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}

json BoardDataBase::updateBoard(const json& info) const {
    size_t id = info["id"];

    if (!checkBoardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {{"table", boardTableName},
                    {"SET", info["info"]},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getBoardInfo(id);
    }

    return response;
}

json BoardDataBase::getBoardInfo(const size_t id) const {
    json request = {{"SELECT", {"*"}},
                    {"FROM", {boardTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    return response;
}

json BoardDataBase::getBoardUsers(const size_t id) const {
    if (!checkBoardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {
        {"SELECT", {"board_id", "user_id", "username", "email", "password", "avatar"}},
        {"FROM", {users2boardsTableName, userTableName}},
        {"JOIN ON", {users2boardsTableName + ".user_id=" + userTableName + ".id"}},
        {"WHERE", {{{"field", users2boardsTableName + ".board_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        response["result"] = json::array({});
        return response;
    }

    return response;
}

json BoardDataBase::getBoardColumns(const size_t id) const {
    if (!checkBoardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {{"SELECT", {"*"}},
                    {"FROM", {columnsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "board_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        response["result"] = json::array({});
        return response;
    }

    return response;
}

json BoardDataBase::getBoardColumn(const size_t id, const size_t column_id) const {
    if (!checkBoardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {{"SELECT", {"*"}},
                    {"FROM", {columnsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE",
                     {{{"field", "id"}, {"value", std::to_string(column_id)}},
                      {{"field", "board_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        if (response["result"] == nullptr) {
            return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Column doesn't exist"}};
        }

        json nested_request = {{"SELECT", {"*"}},
                               {"FROM", {cardsTableName}},
                               {"JOIN ON", {}},
                               {"WHERE", {{{"field", "column_id"}, {"value", std::to_string(column_id)}}}}};

        json nested_response = client->select(nested_request);

        if (nested_response[STATUS_FIELD] == ERROR_STATUS) {
            return nested_response;
        }

        if (nested_response["result"] == nullptr) {
            response["result"][0]["cards"] = json::array({});
        } else {
            response["result"][0]["cards"] = nested_response["result"];
        }
    }

    return response;
}

json BoardDataBase::addColumn(const json& info) const {
    if (!checkBoardExists(info["board_id"])) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Board doesn't exist"}};
    }

    json request = {{"INTO", columnsTableName},
                    {"columns", {"name", "board_id"}},
                    {"VALUES", {info["name"], info["board_id"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        json nested_response = getBoardColumn(info["board_id"], response["result"]);

        return nested_response;
    }

    return response;
}
