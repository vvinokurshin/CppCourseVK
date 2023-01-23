#pragma once

#include "object.h"

struct QCheckListItem : public Object {
    QCheckListItem(const std::string& t, const bool checked, size_t cli)
        : title(t), isChecked(checked), checkListId(cli) {
    }

    json toJson() const override {
        json result;
        result["id"] = id;
        result["name"] = title;
        result["is_checked"] = isChecked;
        result["check_list_id"] = checkListId;
        return result;
    }

    void fromJson(json jsCheckListItem) override {
        id = jsCheckListItem["id"];
        title = jsCheckListItem["name"];
        isChecked = jsCheckListItem["checked"];
        checkListId = jsCheckListItem["checklist_id"];
    }

    std::string title;
    bool isChecked;
    size_t checkListId;
};
