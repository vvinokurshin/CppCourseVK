#pragma once

#include "card.h"
#include "object.h"

struct Column : public Object {
    Column(std::string n = "", size_t di = 0): name(n), boardId(di) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["board_id"] = boardId;
        return result;
    }

    void fromJson(json jsColumn) override {
        id = jsColumn["id"];
        name = jsColumn["name"];
        boardId = jsColumn["board_id"];
    }

    std::string name;
    std::vector<Card> cards;
    size_t boardId;
};
