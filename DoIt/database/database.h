#pragma once

#include <string>

#include "json.hpp"

const std::string STATUS_FIELD = "status";
const std::string ERROR_STATUS = "error";
const std::string SUCCESS_STATUS = "ok";

using json = nlohmann::json;

class DataBase {
  public:
    virtual json select(json) = 0;
    virtual json insert(json) = 0;
    virtual json remove(json) = 0;
    virtual json update(json) = 0;
};
