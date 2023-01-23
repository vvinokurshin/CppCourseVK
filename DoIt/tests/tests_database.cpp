#include "env_settings.hpp"

/* ============ TEST UserDataBase ================ */

TEST(TestAddUser, newUser) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {
        {"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}, {"avatar", nullptr}};
    json response = cl.addUser(request);

    json users = TestEnvironment::getTestDataUsers();
    size_t id = users.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["username"], request["username"]);
    EXPECT_EQ(response["result"][0]["email"], request["email"]);
    EXPECT_EQ(response["result"][0]["password"], request["password"]);
    EXPECT_EQ(response["result"][0]["avatar"], request["avatar"] != nullptr ? request["avatar"] : "");
}

TEST(TestAddUser, oldUser) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {
        {"username", "aaaaaa"}, {"email", "123@mail.ru"}, {"password", "1234556"}, {"avatar", nullptr}};
    json response = cl.addUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveUser, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 1;
    json response = cl.removeUser(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");

    bool res = cl.checkUserExists(id);
    EXPECT_EQ(res, false);
}

TEST(TestRemoveUser, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.removeUser(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestUserValidation, validationPassed) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {{"username", "dima"}, {"password", "12345678"}};
    json response = cl.checkUserValidation(request);

    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], 2);
}

TEST(TestUserValidation, validationFailes) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    json request = {{"username", "dima@"}, {"password", "12345567"}};
    json response = cl.checkUserValidation(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckUserExists, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 2;
    bool response = cl.checkUserExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckUserExists, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    bool response = cl.checkUserExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestUpdateUser, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 2;
    json request = {{"id", id}, {"info", {{"password", "2312313"}}}};
    json response = cl.updateUser(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["password"], request["info"]["password"]);
}

TEST(TestUpdateUser, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json request = {{"id", id}, {"info", {{"password", "2312313"}}}};
    json response = cl.updateUser(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetUserInfo, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 3;
    json response = cl.getUserInfo(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["username"], users[2]["username"]);
    EXPECT_EQ(response["result"][0]["email"], users[2]["email"]);
    EXPECT_EQ(response["result"][0]["password"], users[2]["password"]);
    EXPECT_EQ(response["result"][0]["avatar"], users[2]["avatar"] != nullptr ? users[0]["avatar"] : "");
}

TEST(TestGetUserInfo, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.getUserInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetUserBoards, userExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 2;
    json response = cl.getUserBoards(id);

    json boards = TestEnvironment::getTestDataBoards();
    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], boards[0]["name"]);
    EXPECT_EQ(response["result"][0]["caption"], boards[0]["caption"]);
}

TEST(TestGetUserBoards, userNotExists) {
    UserDataBase cl = TestEnvironment::getUsersClient();
    size_t id = 10;
    json response = cl.getUserBoards(id);

    EXPECT_EQ(response["status"], "error");
}

/* ============ TEST BoardDataBase ================ */

TEST(TestAddBoard, newBoard) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"user_id", 3}, {"name", "aaaaaa"}, {"caption", "bbbbbbbb"}, {"background", nullptr}};
    json response = cl.addBoard(request);

    json boards = TestEnvironment::getTestDataBoards();
    size_t id = boards.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], request["name"]);
    EXPECT_EQ(response["result"][0]["caption"], request["caption"]);
}

TEST(TestRemoveBoard, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 1;
    json response = cl.removeBoard(id);
    json boards = TestEnvironment::getTestDataBoards();

    EXPECT_EQ(response["status"], "ok");

    bool res = cl.checkBoardExists(id);
    EXPECT_EQ(res, false);
}

TEST(TestRemoveBoard, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.removeBoard(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckBoardExists, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 2;
    bool response = cl.checkBoardExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckBoardExists, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    bool response = cl.checkBoardExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestUpdateBoard, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 2;
    json request = {{"id", id}, {"info", {{"name", "123a"}}}};
    json response = cl.updateBoard(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], request["info"]["name"]);
}

TEST(TestUpdateBoard, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json request = {{"id", id}, {"info", {{"name", "123a"}}}};
    json response = cl.updateBoard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardInfo, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 3;
    json response = cl.getBoardInfo(id);
    json boards = TestEnvironment::getTestDataBoards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], boards[2]["name"]);
    EXPECT_EQ(response["result"][0]["caption"], boards[2]["caption"]);
}

TEST(TestGetBoardInfo, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardUsers, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 3;
    json response = cl.getBoardUsers(id);
    json users = TestEnvironment::getTestDataUsers();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["username"], users[2]["username"]);
    EXPECT_EQ(response["result"][0]["email"], users[2]["email"]);
    EXPECT_EQ(response["result"][0]["password"], users[2]["password"]);
    EXPECT_EQ(response["result"][0]["avatar"], users[2]["avatar"] != nullptr ? users[2]["avatar"] : "");
}

TEST(TestGetBoardUsers, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardUsers(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumns, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 3;
    json response = cl.getBoardColumns(id);
    json columns = TestEnvironment::getTestDataColumns();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], columns[5]["name"]);
    EXPECT_EQ(response["result"][0]["board_id"], columns[5]["board_id"]);
    EXPECT_EQ(response["result"][1]["name"], columns[6]["name"]);
    EXPECT_EQ(response["result"][1]["board_id"], columns[6]["board_id"]);
}

TEST(TestGetBoardColumns, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10;
    json response = cl.getBoardUsers(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumn, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 3, column_id = 6;
    json response = cl.getBoardColumn(id, column_id);
    json columns = TestEnvironment::getTestDataColumns(), cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], columns[5]["name"]);
    EXPECT_EQ(response["result"][0]["board_id"], columns[5]["board_id"]);
    EXPECT_EQ(response["result"][0]["cards"][0]["name"], cards[8]["name"]);
    EXPECT_EQ(response["result"][0]["cards"][0]["caption"], cards[8]["caption"]);
    EXPECT_EQ(response["result"][0]["cards"][0]["deadline"],
              cards[8]["deadline"] != nullptr ? cards[8]["deadline"] : "");
    EXPECT_EQ(response["result"][0]["cards"][0]["column_id"], cards[8]["column_id"]);
    EXPECT_EQ(response["result"][0]["cards"][1]["name"], cards[9]["name"]);
    EXPECT_EQ(response["result"][0]["cards"][1]["caption"], cards[9]["caption"]);
    EXPECT_EQ(response["result"][0]["cards"][1]["deadline"],
              cards[9]["deadline"] != nullptr ? cards[9]["deadline"] : "");
    EXPECT_EQ(response["result"][0]["cards"][1]["column_id"], cards[9]["column_id"]);
}

TEST(TestGetBoardColumn, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 10, column_id = 1;
    json response = cl.getBoardColumn(id, column_id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetBoardColumn, ColumnNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    size_t id = 3, column_id = 8;
    json response = cl.getBoardColumn(id, column_id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddColumn, boardExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"name", "aaaaaa"}, {"board_id", 3}};
    json response = cl.addColumn(request);

    json columns = TestEnvironment::getTestDataColumns();
    size_t id = columns.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], request["name"]);
    EXPECT_EQ(response["result"][0]["board_id"], request["board_id"]);
}

TEST(TestAddColumn, boardNotExists) {
    BoardDataBase cl = TestEnvironment::getBoardClient();
    json request = {{"name", "aaaaaa"}, {"board_id", 11}};
    json response = cl.addColumn(request);

    EXPECT_EQ(response["status"], "error");
}

/* ============ TEST CardDataBase ================ */

TEST(TestAddCard, columnExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    json request = {{"name", "first"}, {"caption", "second"}, {"deadline", nullptr}, {"column_id", 2}};
    json response = cl.addCard(request);

    json cards = TestEnvironment::getTestDataCards();
    size_t id = cards.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], request["name"]);
    EXPECT_EQ(response["result"][0]["caption"], request["caption"]);
    EXPECT_EQ(response["result"][0]["deadline"], request["deadline"] != nullptr ? cards[9]["deadline"] : "");
    EXPECT_EQ(response["result"][0]["column_id"], request["column_id"]);
}

TEST(TestAddCard, columnNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    json request = {{"name", "first"}, {"caption", "second"}, {"deadline", nullptr}, {"column_id", 1}};
    json response = cl.addCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCard, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 10;
    json response = cl.removeCard(id);
    json cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");

    bool res = cl.checkCardExists(id);
    EXPECT_EQ(res, false);
}

TEST(TestRemoveCard, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.removeCard(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckCardExists, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    bool response = cl.checkCardExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckCardExists, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 100;
    bool response = cl.checkCardExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestUpdateCard, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json request = {{"id", id}, {"info", {{"column_id", 4}}}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["column_id"], request["info"]["column_id"]);
}

TEST(TestUpdateCard, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json request = {{"id", id}, {"info", {{"column_id", 4}}}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestUpdateCard, columnNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json request = {{"id", id}, {"info", {{"column_id", 111}}}};
    json response = cl.updateCard(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardInfo, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 4;
    json response = cl.getCardInfo(id);
    json cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], id);
    EXPECT_EQ(response["result"][0]["name"], cards[3]["name"]);
    EXPECT_EQ(response["result"][0]["caption"], cards[3]["caption"]);
    EXPECT_EQ(response["result"][0]["deadline"], cards[3]["deadline"] != nullptr ? cards[9]["deadline"] : "");
    EXPECT_EQ(response["result"][0]["column_id"], cards[3]["column_id"]);
}

TEST(TestGetCardInfo, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.getCardInfo(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardCheckLists, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardCheckLists(id);
    json check_lists = TestEnvironment::getTestDataCheckLists();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], check_lists[0]["name"]);
    EXPECT_EQ(response["result"][0]["card_id"], check_lists[0]["card_id"]);
}

TEST(TestGetCardCheckLists, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.getCardCheckLists(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardCheckList, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardCheckList(id, 1);
    json check_lists = TestEnvironment::getTestDataCheckLists(),
         check_lists_items = TestEnvironment::getTestDataCheckListsItems();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], check_lists[0]["name"]);
    EXPECT_EQ(response["result"][0]["card_id"], check_lists[0]["card_id"]);
    EXPECT_EQ(response["result"][0]["items"][0]["name"], check_lists_items[3]["name"]);
    EXPECT_EQ(response["result"][0]["items"][0]["is_checked"], check_lists_items[3]["is_checked"]);
    EXPECT_EQ(response["result"][0]["items"][0]["check_list_id"], check_lists_items[3]["check_list_id"]);
    EXPECT_EQ(response["result"][0]["items"][1]["name"], check_lists_items[4]["name"]);
    EXPECT_EQ(response["result"][0]["items"][1]["is_checked"], check_lists_items[4]["is_checked"]);
    EXPECT_EQ(response["result"][0]["items"][1]["check_list_id"], check_lists_items[4]["check_list_id"]);
}

TEST(TestGetCardCheckList, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 111;
    json response = cl.getCardCheckList(id, 1);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardTags, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    json response = cl.getCardTags(id);
    json tags = TestEnvironment::getTestDataTags();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["name"], tags[2]["name"]);
    EXPECT_EQ(response["result"][0]["color"], tags[2]["color"]);
    EXPECT_EQ(response["result"][0]["card_id"], tags[2]["card_id"]);
}

TEST(TestGetCardTags, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json response = cl.getCardTags(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestGetCardColumn, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 4;
    json response = cl.getCardColumn(id);
    json cards = TestEnvironment::getTestDataCards();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["column_id"], cards[3]["column_id"]);
}

TEST(TestGetCardColumn, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json response = cl.getCardColumn(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestAddTag, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 1;
    json request = {{"name", "abc"}, {"color", "blue"}, {"card_id", card_id}};
    json response = cl.addTag(request);
    json tags = TestEnvironment::getTestDataTags();
    size_t tag_id = tags.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][1]["id"], tag_id);
    EXPECT_EQ(response["result"][1]["name"], request["name"]);
    EXPECT_EQ(response["result"][1]["color"], request["color"]);
    EXPECT_EQ(response["result"][1]["card_id"], request["card_id"]);
}

TEST(TestAddTag, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1111;
    json request = {{"name", "abc"}, {"color", "blue"}, {"card_id", id}};
    json response = cl.addTag(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveTag, tagExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 8;
    json response = cl.removeTag(id);

    EXPECT_EQ(response["status"], "ok");
}

TEST(TestRemoveTag, tagNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 100;
    json response = cl.removeTag(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckTagExists, tagExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 3;
    bool response = cl.checkTagExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckTagExists, tagNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 100;
    bool response = cl.checkTagExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestAddCheckList, cardExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 4;
    json request = {{"name", "for me"}, {"card_id", card_id}};
    json response = cl.addCheckList(request);
    json check_lists = TestEnvironment::getTestDataCheckLists();
    size_t check_list_id = check_lists.size() + 1;

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["id"], check_list_id);
    EXPECT_EQ(response["result"][0]["name"], request["name"]);
    EXPECT_EQ(response["result"][0]["card_id"], request["card_id"]);
}

TEST(TestAddCheckList, cardNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t card_id = 1111;
    json request = {{"name", "for me"}, {"card_id", card_id}};
    json response = cl.addCheckList(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCheckList, checkListExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 4;
    json response = cl.removeCheckList(id);

    EXPECT_EQ(response["status"], "ok");
}

TEST(TestRemoveCheckList, checkListNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 11111;
    json response = cl.removeCheckList(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckCheckListExists, checkListExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    bool response = cl.checkCheckListExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckCheckListExists, checkListNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 100;
    bool response = cl.checkCheckListExists(id);

    EXPECT_EQ(response, false);
}

TEST(TestAddCheckListItem, checkListExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t check_list_id = 2;
    json request = {
        {"name", "done"}, {"is_checked", false}, {"card_id", 5}, {"check_list_id", check_list_id}};
    json response = cl.addCheckListItem(request);
    json check_lists_items = TestEnvironment::getTestDataCheckLists();

    EXPECT_EQ(response["status"], "ok");
    EXPECT_EQ(response["result"][0]["items"][3]["name"], request["name"]);
    EXPECT_EQ(response["result"][0]["items"][3]["is_checked"], request["is_checked"]);
    EXPECT_EQ(response["result"][0]["items"][3]["check_list_id"], request["check_list_id"]);
}

TEST(TestAddCheckListItem, checkListNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t check_list_id = 11111;
    json request = {{"name", "done"}, {"is_checked", false}, {"check_list_id", check_list_id}};
    json response = cl.addCheckListItem(request);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestRemoveCheckListItem, checkListItemExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 7;
    json response = cl.removeCheckListItem(id);

    EXPECT_EQ(response["status"], "ok");
}

TEST(TestRemoveCheckListItem, checkListItemNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 11111;
    json response = cl.removeCheckListItem(id);

    EXPECT_EQ(response["status"], "error");
}

TEST(TestCheckCheckListItemExists, checkListItemExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 1;
    bool response = cl.checkCheckListItemExists(id);

    EXPECT_EQ(response, true);
}

TEST(TestCheckCheckListItemExists, checkListItemNotExists) {
    CardDataBase cl = TestEnvironment::getCardsClient();
    size_t id = 100;
    bool response = cl.checkCheckListItemExists(id);

    EXPECT_EQ(response, false);

    std::cout << TestEnvironment::testsPath() << std::endl;
}
