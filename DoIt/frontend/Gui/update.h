#pragma once

#include "Gui/main_interfaces.h"
#include "gui_user.h"

class Update : public IDate {
  public:
    Update(UiUser _user, QDateTime _date);
    ~Update() = default;

    void setUser(const UiUser& _user);
    UiUser getUser() const;

    virtual void SetDate(QDateTime _date) override;
    virtual QDateTime GetDate() const override;

  private:
    UiUser user;
    // Action action;
    QDateTime date;
};
