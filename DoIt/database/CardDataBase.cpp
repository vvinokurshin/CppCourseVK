#include <iostream>

#include "CardDataBase.h"
#include "allDataBasesInfo.h"

CardDataBase::CardDataBase(std::shared_ptr<DataBase> cl): client(cl) {
}

json CardDataBase::addCard(const json& info) const {
    json request = {{"INTO", cardsTableName},
                    {"columns", {"name", "caption", "deadline", "column_id"}},
                    {"VALUES", {info["name"], info["caption"], info["deadline"], info["column_id"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getCardInfo(response["result"]);
    }

    return response;
}

json CardDataBase::removeCard(const size_t id) const {
    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"FROM", cardsTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

bool CardDataBase::checkCardExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {cardsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}

json CardDataBase::updateCard(const json& info) const {
    size_t id = info["id"];

    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {
        {"table", cardsTableName}, {"SET", info["info"]}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->update(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getCardInfo(id);
    }

    return response;
}

json CardDataBase::getCardInfo(const size_t id) const {
    json request = {{"SELECT", {"*"}},
                    {"FROM", {cardsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    return response;
}

json CardDataBase::getCardCheckLists(const size_t id) const {
    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"SELECT", {"*"}},
                    {"FROM", {checkListTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "card_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        response["result"] = json::array({});
        return response;
    }

    return response;
}

json CardDataBase::getCardCheckList(const size_t id, const size_t check_list_id) const {
    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"SELECT", {"*"}},
                    {"FROM", {checkListTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(check_list_id)}},
                    {{"field", "card_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        if (response["result"] == nullptr) {
            return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Check list doesn't exist"}};
        }

        json nested_request = {{"SELECT", {"*"}},
                               {"FROM", {checkListItemTableName}},
                               {"JOIN ON", {}},
                               {"WHERE", {{{"field", "check_list_id"}, {"value", std::to_string(check_list_id)}}}}};

        json nested_response = client->select(nested_request);

        if (nested_response[STATUS_FIELD] == ERROR_STATUS) {
            return nested_response;
        }

        if (nested_response["result"] == nullptr) {
            response["result"][0]["items"] = json::array({});
        } else {
            response["result"][0]["items"] = nested_response["result"];
        }
    }

    return response;
}

json CardDataBase::getCardTags(const size_t id) const {
    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"SELECT", {"*"}},
                    {"FROM", {tagsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "card_id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS && response["result"] == nullptr) {
        response["result"] = json::array({});
        return response;
    }

    return response;
}

json CardDataBase::getCardColumn(const size_t id) const {
    if (!checkCardExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"SELECT", {"column_id"}},
                    {"FROM", {cardsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};

    json response = client->select(request);

    return response;
}

json CardDataBase::addTag(const json& info) const {
    if (!checkCardExists(info["card_id"])) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"INTO", tagsTableName},
                    {"columns", {"name", "color", "card_id"}},
                    {"VALUES", {info["name"], info["color"], info["card_id"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getCardTags(info["card_id"]);
    }

    return response;
}

json CardDataBase::removeTag(const size_t id) const {
    if (!checkTagExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Tag doesn't exist"}};
    }

    json request = {{"FROM", tagsTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

bool CardDataBase::checkTagExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {tagsTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}

json CardDataBase::addCheckList(const json& info) const {
    if (!checkCardExists(info["card_id"])) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Card doesn't exist"}};
    }

    json request = {{"INTO", checkListTableName},
                    {"columns", {"name", "card_id"}},
                    {"VALUES", {info["name"], info["card_id"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getCardCheckLists(info["card_id"]);
    }

    return response;
}

json CardDataBase::removeCheckList(const size_t id) const {
    if (!checkCheckListExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Check list doesn't exist"}};
    }

    json request = {{"FROM", checkListTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

bool CardDataBase::checkCheckListExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {checkListTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}

json CardDataBase::addCheckListItem(const json& info) const {
    if (!checkCheckListExists(info["check_list_id"])) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Check list doesn't exist"}};
    }

    json request = {{"INTO", checkListItemTableName},
                    {"columns", {"name", "is_checked", "check_list_id"}},
                    {"VALUES", {info["name"], info["is_checked"], info["check_list_id"]}}};

    json response = client->insert(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return getCardCheckList(info["card_id"], info["check_list_id"]);
    }

    return response;
}

json CardDataBase::removeCheckListItem(const size_t id) const {
    if (!checkCheckListItemExists(id)) {
        return {{STATUS_FIELD, ERROR_STATUS}, {"msg", "Check list item doesn't exist"}};
    }

    json request = {{"FROM", checkListItemTableName}, {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->remove(request);
    return response;
}

bool CardDataBase::checkCheckListItemExists(const size_t id) const {
    json request = {{"SELECT", {"id"}},
                    {"FROM", {checkListItemTableName}},
                    {"JOIN ON", {}},
                    {"WHERE", {{{"field", "id"}, {"value", std::to_string(id)}}}}};
    json response = client->select(request);

    if (response[STATUS_FIELD] == SUCCESS_STATUS) {
        return !response["result"].size() == 0;
    }

    return false;
}
