#pragma once

#include <fstream>
#include <iostream>

#include <QDebug>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "net_manager.h"

#include "user.h"

#include "Lib/json.hpp"

using json = nlohmann::json;
using namespace boost;

class UserManager {
  public:
    UserManager(NetManager& netManager): _netManager(netManager) {
    }

    ~UserManager() = default;

    size_t userId() const;

    void authUser(const User& user);

    void regUser(const User& user);

  private:
    NetManager& _netManager;
    size_t _userId = 0;
};
