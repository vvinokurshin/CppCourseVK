#include "auth_window.h"

#include <QLabel>

AuthWindow::AuthWindow(QWidget* parent): QDialog(parent) {
    setWindowTitle("Авторизация");

    // Central
    QWidget* centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");
    centralwidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* centralLayout = new QVBoxLayout(centralwidget);
    centralLayout->setObjectName("centralLayout");
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    // Central content
    QWidget* imageWidget = new QWidget();
    imageWidget->setObjectName("imageWidget");
    imageWidget->setFixedSize(600, 200);

    QWidget* mainWidget = new QWidget();
    mainWidget->setObjectName("mainWidget");
    mainWidget->setFixedSize(600, 300);

    // Main content
    QVBoxLayout* mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Line 1
    QHBoxLayout* line_1 = new QHBoxLayout();
    line_1->setObjectName("line_1");
    line_1->setContentsMargins(30, 0, 100, 0);
    line_1->setSpacing(20);

    // Line 1 content
    QLabel* userNameIcon = new QLabel();
    userNameIcon->setObjectName("userNameIcon");
    userNameIcon->setFixedSize(QSize(20, 20));
    userNameIcon->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    QLabel* userNameLabel = new QLabel(QObject::tr("Имя пользователя"));
    userNameLabel->setObjectName("userNameLabel");
    userNameLabel->setFixedSize(QSize(150, 40));

    QLineEdit* userNameEdit = new QLineEdit();
    userNameEdit->setObjectName("userNameEdit");
    userNameEdit->setFixedSize(QSize(350, 30));
    userNameEdit->setPlaceholderText(QObject::tr("Имя пользователя"));

    // Add line 1 content
    line_1->addWidget(userNameIcon);
    line_1->addWidget(userNameLabel);
    line_1->addWidget(userNameEdit);

    // Line 2
    QHBoxLayout* line_2 = new QHBoxLayout();
    line_2->setSpacing(20);
    line_2->setObjectName("line_2");
    line_2->setContentsMargins(30, 0, 100, 0);

    // Line 2 content
    QLabel* passwordIcon = new QLabel();
    passwordIcon->setObjectName("passwordIcon");
    passwordIcon->setFixedSize(QSize(20, 20));
    passwordIcon->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    QLabel* passwordLabel = new QLabel(QObject::tr("Пароль"));
    passwordLabel->setObjectName("passwordLabel");
    passwordLabel->setFixedSize(QSize(150, 40));

    QLineEdit* passwordEdit = new QLineEdit();
    passwordEdit->setObjectName("passwordEdit");
    passwordEdit->setFixedSize(QSize(350, 30));
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText(QObject::tr("Пароль"));

    // Add line 2 content
    line_2->addWidget(passwordIcon);
    line_2->addWidget(passwordLabel);
    line_2->addWidget(passwordEdit);

    // Line 3
    QHBoxLayout* line_3 = new QHBoxLayout();
    line_3->setObjectName("line_3");
    line_3->setContentsMargins(30, 0, 0, 0);

    // Line 3 content
    QPushButton* registerLabel = new QPushButton(QObject::tr("Зарегистрироваться"));
    registerLabel->setObjectName("registerLabel");
    registerLabel->setFixedSize(QSize(155, 40));

    // Add line 3 content
    line_3->addWidget(registerLabel);
    line_3->setAlignment(registerLabel, Qt::AlignLeft);

    // Line 4
    QHBoxLayout* line_4 = new QHBoxLayout();
    line_4->setObjectName("line_4");
    line_4->setContentsMargins(0, 0, 0, 10);

    // Line 4 content
    QPushButton* loginButton = new QPushButton(QObject::tr("Войти"));
    loginButton->setObjectName("loginButton");
    loginButton->setFixedSize(QSize(200, 40));

    // Add line 4 content
    line_4->addWidget(loginButton);

    // Add Main content
    mainLayout->addLayout(line_1);
    mainLayout->addLayout(line_2);
    mainLayout->addLayout(line_3);
    mainLayout->addLayout(line_4);

    // Add central content
    centralLayout->addWidget(imageWidget);
    centralLayout->addWidget(mainWidget);

    // Fixed size
    setFixedSize(600, 500);

    // Styles //
    this->setStyleSheet(
        QString::fromUtf8("* {\n"
                          "  	font-family: \"Times New Roman\", Times, serif;\n"
                          " 	font-size: 18px;\n"
                          "  	font-weight: Normal;\n"
                          "}\n"
                          "\n"
                          "#imageWidget {\n"
                          "	background-color: white;\n"
                          "	border-image: url(Gui/resources/img/sign_in.png);\n"
                          "   max-width: 600px;\n"
                          "   min-height: 200px;\n"
                          "\n"
                          "   border-top-left-radius: 20px;\n"
                          "   border-top-right-radius: 20px;\n"
                          "}\n"
                          "\n"
                          "#mainWidget {\n"
                          "	background-color: #ffffff;\n"
                          "}\n"
                          "\n"
                          "#userNameLabel, #passwordLabel {\n"
                          "	color: gray;\n"
                          "}\n"
                          "#userNameIcon {\n"
                          "	image: url(Gui/resources/icons/user_black.png);\n"
                          "}\n"
                          "\n"
                          "#passwordIcon {\n"
                          "	image: url(Gui/resources/icons/lock.png);\n"
                          "}\n"
                          "\n"
                          "#userNameEdit, #passwordEdit {\n"
                          "	border: 2px solid rgb(37, 39, 48);\n"
                          "	border-radius: 10px;\n"
                          "	color: hsl(194, 4%, 53%);\n"
                          "   font-style: italic;\n"
                          "	padding-left: 10px;\n"
                          "	background-color: rgb(34, 36, 44);\n"
                          "}\n"
                          "\n"
                          "#userNameEdit:hover, #passwordEdit:hover {\n"
                          "	border: 2px solid rgb(48, 50, 62);\n"
                          "}\n"
                          "\n"
                          "#userNameEdit:hover, #passwordEdit:hover {\n"
                          "	border: 2px solid rgb(85, 170, 255);\n"
                          "	background-color: rgb(43, 45, 56);\n"
                          "}\n"
                          "\n"
                          "#registerLabel {\n"
                          "	color: #999;\n"
                          "	border: 0px;\n"
                          "}\n"
                          "\n"
                          "#registerLabel:hover {\n"
                          "	color: green;\n"
                          "}\n"
                          "\n"
                          "#loginButton {\n"
                          "	border-style: solid;\n"
                          "	border-color: #9999aa;\n"
                          "	border-radius: 10px;\n"
                          "	color: white;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#loginButton:enabled {\n"
                          "	color: white;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#loginButton:pressed {\n"
                          "	color: #fffffe;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#loginButton:hover:!pressed {\n"
                          "	color: #0c2f70;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#loginButton:disabled {\n"
                          "	color: #ffffff;\n"
                          "	background-color: #aaaaaa;\n"
                          "}"));

    // connections
    connect(loginButton, &QPushButton::clicked, this, &AuthWindow::authClickedSlot);
    connect(registerLabel, &QPushButton::clicked, this, &AuthWindow::openRegSignal);
}

AuthWindow::~AuthWindow() {
}
