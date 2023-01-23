#pragma once

#include <iostream>
#include <thread>

#include "gui_manager.h"
#include "net_manager.h"
#include "user_manager.h"

#include "board.h"
#include "user.h"

#include "Lib/json.hpp"

using json = nlohmann::json;

class MainManager : public QObject {
    Q_OBJECT
  public:
    explicit MainManager(QObject* parent = nullptr);

    ~MainManager() override = default;

    void ping();

    void getAllUserData();

    void getUserBoards();

    void getColumns();

    void getCards();

  public slots:

    void authSlot(const User& user);

    void regSlot(const User& user);

    void updateDataSlot();

    void showBoardsSlot();

    void addObjectSlot(Object& obj, ObjType objType);

    void deleteObjectSlot(size_t id, ObjType objType);

    void updateObjectSlot(Object& obj, ObjType objType);

    void logoutSlot();

    void addUserSlot(User& user, const size_t boardId);

  signals:

    void showBoardsSignal();

    void showBoardSignal(Board& board);

    void sendBoardsSignal(std::vector<Board>& boards);

    void sendColumnsSignal(std::vector<Column>& columns);

    void sendCardsSignal(std::vector<Card>& cards);

  private:
    static std::string _objType2Str(ObjType objType) {
        switch (objType) {
            case BOARD:
                return "board";
            case COLUMN:
                return "column";
            case CARD:
                return "card";
            case TAG:
                return "tag";
            case CHECK_LIST:
                return "check_list";
            case CHECK_LIST_ITEM:
                return "check_list_item";
        }
        return "";
    }

  private:
    NetManager _netManager;
    GuiManager _guiManager;
    UserManager _userManager;

    std::vector<Board> _boards;
    Board _board;
};
