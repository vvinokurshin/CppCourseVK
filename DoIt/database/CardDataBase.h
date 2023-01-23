#pragma once

#include <string>

#include "PostgreDataBase.h"
#include "database.h"

class CardDataBase {
  public:
    CardDataBase() = default;
    CardDataBase(std::shared_ptr<DataBase> client);
    json addCard(const json& info) const;
    json removeCard(const size_t id) const;
    bool checkCardExists(const size_t id) const;
    json updateCard(const json& info) const;
    json getCardInfo(const size_t id) const;
    json getCardCheckLists(const size_t id) const;
    json getCardCheckList(const size_t id, const size_t check_list_id) const;
    json getCardTags(const size_t id) const;
    json getCardColumn(const size_t id) const;
    json addTag(const json& info) const;
    json removeTag(const size_t id) const;
    bool checkTagExists(const size_t id) const;
    json addCheckList(const json& info) const;
    json removeCheckList(const size_t id) const;
    bool checkCheckListExists(const size_t id) const;
    json addCheckListItem(const json& info) const;
    json removeCheckListItem(const size_t id) const;
    bool checkCheckListItemExists(const size_t id) const;

  private:
    std::shared_ptr<DataBase> client;
};