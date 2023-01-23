#pragma once

#include "Gui/main_interfaces.h"
#include "gui_user.h"

class Comment : public IText, IDate {
  public:
    Comment(QString _text, UiUser _user, QDateTime _date);
    ~Comment() = default;

    void setUser(const UiUser& _user);
    UiUser getUser() const;

    virtual void SetText(const QString& _text) override;
    virtual QString GetText() const override;

    virtual void SetDate(QDateTime _date) override;
    virtual QDateTime GetDate() const override;

    friend bool operator==(const Comment& l, const Comment& r);

  private:
    QString text;
    UiUser user;
    QDateTime date;
};
