#include "comment.h"

Comment::Comment(QString _text, UiUser _user, QDateTime _date): text(_text), user(_user), date(_date) {
}

void Comment::setUser(const UiUser& _user) {
    user = _user;
}

UiUser Comment::getUser() const {
    return user;
}

void Comment::SetText(const QString& _text) {
    text = _text;
}

QString Comment::GetText() const {
    return text;
}

void Comment::SetDate(QDateTime _date) {
    date = _date;
}

QDateTime Comment::GetDate() const {
    return date;
}

bool operator==(const Comment& l, const Comment& r) {
    if (l.text == r.text && l.user == r.user && l.date == r.date)
        return true;

    return false;
}
