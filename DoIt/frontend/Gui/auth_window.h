#pragma once

#include <iostream>

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>

#include "user.h"

class AuthWindow : public QDialog {
    Q_OBJECT

  public slots:

    void authClickedSlot() {
        QLineEdit* username = findChild<QLineEdit*>("userNameEdit");
        QLineEdit* password = findChild<QLineEdit*>("passwordEdit");
        User user;
        user.username = username->text().toStdString();
        user.password = password->text().toStdString();

        emit authSignal(user);
    }

    void openRegSlot() {
    }

  signals:

    void authSignal(const User& user);

    void openRegSignal();

  public:
    explicit AuthWindow(QWidget* parent = nullptr);

    ~AuthWindow();
};
