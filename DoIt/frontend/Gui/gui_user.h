#pragma once

#include <QString>

class UiUser {
  public:
    UiUser(QString _name);
    ~UiUser() = default;

    UiUser(const UiUser& other);
    UiUser& operator=(const UiUser& other);

    void setName(const QString& _name);
    QString getName() const;

    friend bool operator==(const UiUser& l, const UiUser& r);

  private:
    QString name;
    // image
};
