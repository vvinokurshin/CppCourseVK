#pragma once

#include <QString>

#include <cstddef>
#include <iostream>
#include <utility>

#include "column.h"
#include "object.h"

struct Board : public Object {
    Board(const std::string& n = "", const std::string& desc = "", const std::string& bg = "")
        : name(n), caption(desc), background(bg) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = name;
        result["caption"] = caption;
        result["background"] = background;
        return result;
    }

    void fromJson(json jsBoard) override {
        id = jsBoard["id"];
        name = jsBoard["name"];
        caption = jsBoard["caption"];
        background = jsBoard["background"];
    }

    std::string name;
    std::string caption;
    std::string background;
    std::vector<Column> columns;
};
