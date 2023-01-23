#pragma once

#include "check_list.h"
#include "object.h"
#include "tag.h"

struct Card : public Object {
    Card(const std::string& t = "", const std::string& d = "", size_t col_id = 0)
        : name(t), caption(d), columnId(col_id) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["caption"] = caption;
        result["deadline"] = nullptr;
        result["column_id"] = columnId;
        return result;
    }

    void fromJson(json jsCard) override {
        id = jsCard["id"];
        name = jsCard["name"];
        caption = jsCard["caption"];
        columnId = jsCard["column_id"];
    }

    std::string name;
    std::string caption;
    size_t columnId;

    std::vector<QTag> tags;
    std::vector<CheckList> checkLists;
};
