#include "database_interaction.h"

std::string DatabaseInteraction::on_login(json msg_json)
{
    json result = clUser.checkUserValidation(msg_json["data"]);
    return convert(result);
}

json DatabaseInteraction::getUsers() {
    json resp = clUser.getUsers();
    return resp["result"];
}

json DatabaseInteraction::analyze_msg(json msg_json)
    {
        std::cout << "Got Json: " << msg_json << std::endl;
        if (msg_json["cmd"] == "database_get") return on_get_content(msg_json);
        else if (msg_json["cmd"] == "database_create") return on_create_content(msg_json);
        else if (msg_json["cmd"] == "database_change") return on_change_content(msg_json);
        else if (msg_json["cmd"] == "database_delete") return on_delete_content(msg_json);
        else return on_invalid_msg();
    }

json DatabaseInteraction::on_get_content(json msg_json) 
{
    json result;
    if (msg_json["content"] == "board_info")
    {
        result = cl.getBoardInfo(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_columns")
    {
        result = cl.getBoardColumns(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_users")
    {
        result = cl.getBoardUsers(msg_json["board_id"]);
    }
    else if (msg_json["content"] == "board_column")
    {
        result = cl.getBoardColumn(msg_json["board_id"],msg_json["column_id"]);
    }
    else if (msg_json["content"] == "user_info")
    {
        result = clUser.getUserInfo(msg_json["user_id"]);
    }
    else if (msg_json["content"] == "user_boards")
    {
        result = clUser.getUserBoards(msg_json["user_id"]);
    }
    else if (msg_json["content"] == "card_info")
    {
        result = clCard.getCardInfo(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_checklists")
    {
        result = clCard.getCardCheckLists(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_tags")
    {
        result = clCard.getCardTags(msg_json["card_id"]);
    }
    else if (msg_json["content"] == "card_column")
    {
        result = clCard.getCardColumn(msg_json["card_id"]);
    }
    return result;
}

json DatabaseInteraction::on_create_content(json msg_json)
{
    json data = msg_json["data"];
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.addBoard(data);
    }
    else if (msg_json["content"] == "user")
    {
        result = clUser.addUser(data);
    }
    else if (msg_json["content"] == "column")
    {
        result = cl.addColumn(data);
    }
    else if (msg_json["content"] == "card")
    {
        result = clCard.addCard(data);
    }
    else if (msg_json["content"] == "tag")
    {
        result = clCard.addTag(data);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = clCard.addCheckList(data);
    }
    else if (msg_json["content"] == "checklist_item")
    {
        result = clCard.addCheckListItem(data);
    }
    return result;
}

json DatabaseInteraction::on_change_content(json msg_json)
{
    json data = msg_json["data"];
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.updateBoard(data);
    }
    else if (msg_json["content"] == "user")
    {
        result = clUser.updateUser(data);
    }
    else if (msg_json["content"] == "card")
    {
        result = clCard.updateCard(data);
    }
    return result;
}

json DatabaseInteraction::on_delete_content(json msg_json)
{
    json result;
    if (msg_json["content"] == "board")
    {
        result = cl.removeBoard(msg_json["id"]);
    }
    else if (msg_json["content"] == "user")
    {
        result = clUser.removeUser(msg_json["id"]);
    }
    else if (msg_json["content"] == "column")
    {
        result = cl.removeColumn(msg_json["id"]);
    }
    else if (msg_json["content"] == "card")
    {
        result = clCard.removeCard(msg_json["id"]);
    }
    else if (msg_json["content"] == "tag")
    {
        result = clCard.removeTag(msg_json["id"]);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = clCard.removeCheckList(msg_json["id"]);
    }
    else if (msg_json["content"] == "checklist")
    {
        result = clCard.removeCheckListItem(msg_json["id"]);
    }
    return result;
}

json DatabaseInteraction::on_invalid_msg()
{
    json result;
    result["response"] = "invalid msg";
    return result;
}
