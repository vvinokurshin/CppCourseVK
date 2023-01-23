#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class UserDataBase {
  public:
    UserDataBase() = default;
    UserDataBase(std::shared_ptr<DataBase> client);
    json addUser(const json& info) const;
    json getUsers() const;
    json removeUser(const size_t id) const;
    json checkUserValidation(const json& info) const;
    bool checkUserExists(const size_t id) const;
    json updateUser(const json& info) const;
    json getUserInfo(const size_t id) const;
    json getUserBoards(const size_t id) const;

  private:
    std::shared_ptr<DataBase> client;
};