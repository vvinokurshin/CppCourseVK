#pragma once

#include "PostgreDataBase.h"
#include "BoardDataBase.h"
#include "UserDataBase.h"
#include "CardDataBase.h"

#include "json.hpp"
using json = nlohmann::json;

std::shared_ptr<PostgreDataBase> getPgClient();

BoardDataBase getBoardClient();

CardDataBase getCardClient();

UserDataBase getUserClient();
