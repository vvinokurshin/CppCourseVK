#pragma once

#include <cstddef>
#include <utility>

#include "column.h"
#include "object.h"

struct User : public Object {
    User(const std::string& un = "", const std::string& p = ""): username(un), password(p) {
    }

    User(const std::string& un, const std::string& p, const std::string& e, const std::string& ap)
        : username(un), password(p), email(e), avatar(ap) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["username"] = username;
        result["password"] = password;
        result["email"] = email;
        result["avatar"] = avatar;
        return result;
    }

    void fromJson(json jsUser) override {
        id = jsUser["id"];
        username = jsUser["username"];
        password = jsUser["password"];
        email = jsUser["email"];
        avatar = jsUser["avatar"];
    }

    std::string username;
    std::string password;
    std::string email;
    std::string avatar;
};
