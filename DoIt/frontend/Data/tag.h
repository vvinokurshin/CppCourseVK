#pragma once

#include "object.h"

struct QTag : public Object {
    QTag(const std::string& n, const std::string& c, size_t ci): name(n), color(c), cardId(ci) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["color"] = color;
        result["card_id"] = cardId;
        return result;
    }

    void fromJson(json jsTag) override {
        id = jsTag["id"];
        name = jsTag["name"];
        color = jsTag["color"];
        cardId = jsTag["card_id"];
    }

    std::string name;
    std::string color;
    size_t cardId;
};
