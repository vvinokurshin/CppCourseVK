#pragma once

#include <iostream>
#include <vector>

const std::string userTableName = "users";
const std::vector<std::string> userTableColumns = {"id", "username", "email", "password", "avatar"};

const std::string boardTableName = "boards";
const std::vector<std::string> boardTableColumns = {"id", "name", "caption", "background"};

const std::string users2boardsTableName = "users2boards";
const std::vector<std::string> users2boardsTableColumns = {"user_id", "board_id"};

const std::string columnsTableName = "columns";
const std::vector<std::string> columnsTableColumns = {"id", "name", "board_id"};

const std::string cardsTableName = "cards";
const std::vector<std::string> cardsTableColumns = {"id", "name", "caption", "deadline", "column_id"};

const std::string tagsTableName = "tags";
const std::vector<std::string> tagsTableColumns = {"id", "name", "color", "card_id"};

const std::string checkListTableName = "check_lists";
const std::vector<std::string> checkListTableColumns = {"id", "name", "card_id"};

const std::string checkListItemTableName = "check_lists_items";
const std::vector<std::string> checkListItemTableColumns = {"id", "name", "is_checked", "check_list_id"};