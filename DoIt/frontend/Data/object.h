#pragma once

#include "json.hpp"
#include <cstddef>

using json = nlohmann::json;

enum ObjType {
    BOARD,
    COLUMN,
    CARD,
    TAG,
    CHECK_LIST,
    CHECK_LIST_ITEM
};

struct Object {
    size_t id;

    Object(): id(0) {
    }

    Object(size_t i): id(i) {
    }

    virtual ~Object() = default;

    virtual json toJson() const = 0;

    virtual void fromJson(json) = 0;
};
