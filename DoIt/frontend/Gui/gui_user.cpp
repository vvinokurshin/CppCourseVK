#include "gui_user.h"

UiUser::UiUser(QString _name): name(_name) {
}

UiUser::UiUser(const UiUser& other) {
    name = other.name;
}

UiUser& UiUser::operator=(const UiUser& other) {
    if (this != &other) {
        this->~UiUser();
        new (this) UiUser(other.name);
    }

    return *this;
}

void UiUser::setName(const QString& _name) {
    name = _name;
}

QString UiUser::getName() const {
    return name;
}

bool operator==(const UiUser& l, const UiUser& r) {
    if (l.name == r.name)
        return true;

    return false;
}
