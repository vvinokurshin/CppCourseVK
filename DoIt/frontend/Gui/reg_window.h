#pragma once

#include <QDialog>

#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "user.h"
#include <QValidator>
#include <iostream>
#include <qt5/QtWidgets/QMessageBox>

class RegWindow : public QDialog {
    Q_OBJECT

  public slots:
    void regClickedSlot() {
        QLineEdit* usernameEdit = findChild<QLineEdit*>("userNameEdit");
        QLineEdit* emailEdit = findChild<QLineEdit*>("emaildEdit");
        QLineEdit* passwordEdit = findChild<QLineEdit*>("passwordEdit");
        QLineEdit* passwordRepEdit = findChild<QLineEdit*>("repeatPasswordEdit");

        if (passwordEdit->text() != passwordRepEdit->text()) {
            std::cout << "Incorrect Passwords";
            return;
        }

        User user;
        user.username = usernameEdit->text().toStdString();
        user.email = emailEdit->text().toStdString();
        user.password = passwordEdit->text().toStdString();

        emit regSignal(user);
    }

  signals:
    void regSignal(const User& user);
    void openAuthSignal();

  public:
    explicit RegWindow(QWidget* parent = nullptr);
    ~RegWindow();
};
