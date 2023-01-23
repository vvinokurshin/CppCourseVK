#include "user_manager.h"

size_t UserManager::userId() const {
    return _userId;
}

void UserManager::authUser(const User& user) {
    json data;
    data["cmd"] = "login";
    data["data"] = user.toJson();
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    _userId = resp["result"][0]["id"];
}

void UserManager::regUser(const User& user) {
    json data = user.toJson();
    data["cmd"] = "register";
    std::string request = data.dump();

    int err = 0;
    _netManager.connect();
    _netManager.sendMessage(request + "\n", err);
    std::string response = _netManager.getMessage(err);
    json resp = json::parse(response);
    _netManager.disconnect();

    _userId = resp["result"][0]["id"];
}
