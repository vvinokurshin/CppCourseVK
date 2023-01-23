#include "main_manager.h"

MainManager::MainManager(QObject* parent)
    : QObject(parent), _netManager(), _guiManager(), _userManager(_netManager) {
    // connections
    connect(this, &MainManager::showBoardsSignal, this, &MainManager::showBoardsSlot);

    // from gui manager
    connect(&_guiManager, &GuiManager::authSignal, this, &MainManager::authSlot);
    connect(&_guiManager, &GuiManager::regSignal, this, &MainManager::regSlot);
    connect(&_guiManager, &GuiManager::addObjectSignal, this, &MainManager::addObjectSlot);
    connect(&_guiManager, &GuiManager::delObjectSignal, this, &MainManager::deleteObjectSlot);
    connect(&_guiManager, &GuiManager::updateObjectSignal, this, &MainManager::updateObjectSlot);

    // from net manager
    connect(&_netManager, &NetManager::updateDataSignal, this, &MainManager::updateDataSlot);
}

void MainManager::ping() {
    try {
        _netManager.pingLoop(_userManager.userId());
    } catch (boost::system::system_error& err) {
        std::cout << "Failed to ping\n";
        std::cout << "Try to reconnect\n";
        ping();
    }
}

void MainManager::getAllUserData() {
    _boards.clear();

    getUserBoards();
    getColumns();
    getCards();

    showBoardsSignal();
}

void MainManager::getUserBoards() {
    json data;
    data["cmd"] = "database_get";
    data["content"] = "user_boards";
    data["user_id"] = _userManager.userId();
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    _netManager.disconnect();

    json resp = json::parse(response);

    Board board;
    for (auto &jsBoard : resp["result"]) {
        jsBoard["id"] = jsBoard["board_id"];
        board.fromJson(jsBoard);
        _boards.push_back(board);
    }
}

void MainManager::getColumns() {
    json data;
    data["cmd"] = "database_get";
    data["content"] = "board_columns";
    for (auto& board : _boards) {
        data["board_id"] = board.id;
        std::string request = data.dump();
        int err = 0;
        _netManager.connect();
        _netManager.sendMessage(request + "\n", err);
        std::string response = _netManager.getMessage(err);
        json resp = json::parse(response);
        _netManager.disconnect();

        Column col;
        for (const auto &jsCol : resp["result"]) {
            col.fromJson(jsCol);
            board.columns.push_back(col);
        }
    }
}

void MainManager::getCards() {
    json data;
    data["cmd"] = "database_get";
    data["content"] = "board_column";
    for (auto& board : _boards) {
        for (auto& column : board.columns) {
            data["board_id"] = board.id;
            data["column_id"] = column.id;
            std::string request = data.dump();
            int err = 0;
            _netManager.connect();
            _netManager.sendMessage(request + "\n", err);
            std::string response = _netManager.getMessage(err);
            json resp = json::parse(response);
            _netManager.disconnect();

            Card card;
            for (const auto &jsCard : resp["result"][0]["cards"]) {
                card.fromJson(jsCard);
                column.cards.push_back(card);
            }
        }
    }
}

// public slots
void MainManager::authSlot(const User& user) {
    _userManager.authUser(user);

    // пользователь авторизовался, показываем на ui виджет загрузки данных пользователя
    _guiManager.showLoadAllData();

    // в отдельном потоке получаем данные пользователя
    std::thread thr_first_get_boards([&]() { getAllUserData(); });
    thr_first_get_boards.detach();

    // Также начинаем опрашивать сервер об изменениях
    //    std::thread thr_ping([&]() { ping(); });
    //    thr_ping.detach();
}

void MainManager::regSlot(const User& user) {
    _userManager.regUser(user);

    _guiManager.showLoadAllData();

    std::thread thr_first_get_boards([&]() { getAllUserData(); });
    thr_first_get_boards.detach();
}

void MainManager::updateDataSlot() {
    std::thread thr_first_get_boards([&]() { getAllUserData(); });
    thr_first_get_boards.detach();
}

void MainManager::showBoardsSlot() {
    _guiManager.deleteLoad();
    _guiManager.showBoards(_boards);
}

void MainManager::addObjectSlot(Object& obj, ObjType objType) {
    json data;
    data["cmd"] = "database_create";
    data["content"] = _objType2Str(objType);
    data["data"] = obj.toJson();
    data["data"]["user_id"] = _userManager.userId();

    std::string request = data.dump();
    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    obj.id = resp["result"][0]["id"];  // set id for new object

    // также производим изменения локально
    if (objType == BOARD) {
        Board& board = dynamic_cast<Board&>(obj);
        _boards.push_back(board);
    } else if (objType == COLUMN) {
        Column& col = dynamic_cast<Column&>(obj);
        for (auto& board : _boards) {
            if (board.id == col.boardId) {
                board.columns.push_back(col);
            }
        }
    } else if (objType == CARD) {
        Card& card = dynamic_cast<Card&>(obj);
        for (auto& board : _boards) {
            for (auto& column : board.columns) {
                if (column.id == card.columnId) {
                    column.cards.push_back(card);
                }
            }
        }
    }
    _guiManager.showBoards(_boards);
}

void MainManager::deleteObjectSlot(size_t id, ObjType objType) {
    json data;
    data["cmd"] = "database_delete";
    data["content"] = _objType2Str(objType);
    data["id"] = id;
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    // производим изменения локально
    if (objType == BOARD) {
        for (auto it = _boards.begin(); it != _boards.end(); ++it) {
            if (it->id == id) {
                _boards.erase(it);
                break;
            }
        }
    } else if (objType == COLUMN) {
        for (auto& board : _boards) {
            for (auto it = board.columns.begin(); it != board.columns.end(); ++it) {
                if (it->id == id) {
                    board.columns.erase(it);
                    break;
                }
            }
        }
    } else if (objType == CARD) {
        for (auto& board : _boards) {
            for (auto& column : board.columns) {
                for (auto it = column.cards.begin(); it != column.cards.end(); ++it) {
                    if (it->id == id) {
                        column.cards.erase(it);
                        break;
                    }
                }
            }
        }
    }

    _guiManager.showBoards(_boards);
}

void MainManager::updateObjectSlot(Object& obj, ObjType objType) {
    json data;
    data["cmd"] = "database_change";
    data["content"] = _objType2Str(objType);
    json obj_json = obj.toJson();
    data["data"]["id"] = obj_json["id"];
    obj_json.erase("id");
    data["data"]["info"] = obj_json;
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    // производим изменения локально
    if (objType == CARD) {
        Card& card = dynamic_cast<Card&>(obj);
        for (auto& board : _boards) {
            for (auto& column : board.columns) {
                for (auto& c : column.cards) {
                    if (card.id == c.id) {
                        c = card;
                        break;
                    }
                }
            }
        }
    }
    _guiManager.showBoards(_boards);
}

void MainManager::logoutSlot() {
    json data;
    data["cmd"] = "logout";
    std::string request = data.dump();

    int err = 0;
    _netManager.sendMessage(request + "\n", err);
}

void MainManager::addUserSlot(User& user, const size_t boardId) {
    json data = user.toJson();
    data["cmd"] = "add user to board";
    data["board_id"] = boardId;
    std::string request = data.dump();

    int err = 0;
    _netManager.sendMessage(request + '\n', err);
}
