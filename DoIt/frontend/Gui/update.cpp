#include "update.h"

Update::Update(UiUser _user, QDateTime _date): user(_user), date(_date) {
}

void Update::setUser(const UiUser& _user) {
    user = _user;
}

UiUser Update::getUser() const {
    return user;
}

void Update::SetDate(QDateTime _date) {
    date = _date;
}

QDateTime Update::GetDate() const {
    return date;
}
