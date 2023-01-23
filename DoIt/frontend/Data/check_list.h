#pragma once

#include "check_list_item.h"
#include "object.h"

struct CheckList : public Object {
    CheckList(const std::string& t, size_t ci): title(t), cardId(ci) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = title;
        result["card_id"] = cardId;
        return result;
    }

    void fromJson(json jsCheckList) override {
        id = jsCheckList["id"];
        title = jsCheckList["name"];
        cardId = jsCheckList["card_id"];
    }

    std::string title;
    std::vector<QCheckListItem> items;
    size_t cardId;
};
