#include "reg_window.h"

RegWindow::RegWindow(QWidget* parent): QDialog(parent) {
    setWindowTitle("Регистрация");

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
    userNameEdit->setValidator(
        new QRegularExpressionValidator(QRegularExpression("[A-Za-z][A-Za-z0-9_]{7,29}")));

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
    QLabel* emailIcon = new QLabel();
    emailIcon->setObjectName("emailIcon");
    emailIcon->setFixedSize(QSize(20, 20));
    emailIcon->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    QLabel* emailLabel = new QLabel(QObject::tr("Почта"));
    emailLabel->setObjectName("emailLabel");
    emailLabel->setFixedSize(QSize(150, 40));

    QLineEdit* emaildEdit = new QLineEdit();
    emaildEdit->setObjectName("emaildEdit");
    emaildEdit->setFixedSize(QSize(350, 30));
    emaildEdit->setEchoMode(QLineEdit::Password);
    emaildEdit->setPlaceholderText(QObject::tr("vasiliy.pupkin@mail.ru"));
    emaildEdit->setValidator(new QRegularExpressionValidator(
        QRegularExpression("([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})")));

    // Add line 2 content
    line_2->addWidget(emailIcon);
    line_2->addWidget(emailLabel);
    line_2->addWidget(emaildEdit);

    // Line 3
    QHBoxLayout* line_3 = new QHBoxLayout();
    line_3->setSpacing(20);
    line_3->setObjectName("line_3");
    line_3->setContentsMargins(30, 0, 100, 0);

    // Line 3 content
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
    // Minimum eight characters, at least one uppercase letter, one lowercase
    // letter and one number
    passwordEdit->setValidator(new QRegularExpressionValidator(
        QRegularExpression("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}")));

    // Add line 3 content
    line_3->addWidget(passwordIcon);
    line_3->addWidget(passwordLabel);
    line_3->addWidget(passwordEdit);

    // Line 4
    QHBoxLayout* line_4 = new QHBoxLayout();
    line_4->setSpacing(20);
    line_4->setObjectName("line_4");
    line_4->setContentsMargins(30, 0, 100, 0);

    // Line 4 content
    QLabel* repeatPasswordIcon = new QLabel();
    repeatPasswordIcon->setObjectName("repeatPasswordIcon");
    repeatPasswordIcon->setFixedSize(QSize(20, 20));
    repeatPasswordIcon->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    QLabel* repeatPasswordLabel = new QLabel(QObject::tr("Повторите пароль"));
    repeatPasswordLabel->setObjectName("repeatPasswordLabel");
    repeatPasswordLabel->setFixedSize(QSize(150, 40));

    QLineEdit* repeatPasswordEdit = new QLineEdit();
    repeatPasswordEdit->setObjectName("repeatPasswordEdit");
    repeatPasswordEdit->setFixedSize(QSize(350, 30));
    repeatPasswordEdit->setEchoMode(QLineEdit::Password);
    repeatPasswordEdit->setPlaceholderText(QObject::tr("Пароль"));
    // Minimum eight characters, at least one uppercase letter, one lowercase
    // letter and one number
    repeatPasswordEdit->setValidator(new QRegularExpressionValidator(
        QRegularExpression("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}")));

    // Add line 4 content
    line_4->addWidget(repeatPasswordIcon);
    line_4->addWidget(repeatPasswordLabel);
    line_4->addWidget(repeatPasswordEdit);

    // Line 5
    QHBoxLayout* line_5 = new QHBoxLayout();
    line_5->setObjectName("line_5");
    line_5->setContentsMargins(30, 0, 0, 0);

    // Line 5 content
    QPushButton* loginLabel = new QPushButton(QObject::tr("Войти"));
    loginLabel->setObjectName("loginLabel");
    loginLabel->setFixedSize(QSize(155, 40));

    // Add line 5 content
    line_5->addWidget(loginLabel);
    line_5->setAlignment(loginLabel, Qt::AlignLeft);

    // Line 6
    QHBoxLayout* line_6 = new QHBoxLayout();
    line_6->setObjectName("line_6");
    line_6->setContentsMargins(0, 0, 0, 10);

    // Line 6 content
    QPushButton* regButton = new QPushButton(QObject::tr("Зарегистрироваться"));
    regButton->setObjectName("regButton");
    regButton->setFixedSize(QSize(200, 40));

    // Add line 6 content
    line_6->addWidget(regButton);

    // Add Main content
    mainLayout->addLayout(line_1);
    mainLayout->addLayout(line_2);
    mainLayout->addLayout(line_3);
    mainLayout->addLayout(line_4);
    mainLayout->addLayout(line_5);
    mainLayout->addLayout(line_6);

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
                          "	border-image: url(Gui/resources/img/registration.png);\n"
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
                          "#userNameLabel, #emailLabel, #passwordLabel, #repeatPasswordLabel {\n"
                          "	color: gray;\n"
                          "}\n"
                          "#userNameIcon {\n"
                          "	image: url(Gui/resources/icons/user_black.png);\n"
                          "}\n"
                          "\n"
                          "#emailIcon {\n"
                          "	image: url(Gui/resources/icons/email.png);\n"
                          "}\n"
                          "\n"
                          "#passwordIcon, #repeatPasswordIcon {\n"
                          "	image: url(Gui/resources/icons/lock.png);\n"
                          "}\n"
                          "\n"
                          "#userNameEdit, #emaildEdit, #passwordEdit, #repeatPasswordEdit {\n"
                          "	border: 2px solid rgb(37, 39, 48);\n"
                          "	border-radius: 10px;\n"
                          "	color: hsl(194, 4%, 53%);\n"
                          "   font-style: italic;\n"
                          "	padding-left: 10px;\n"
                          "	background-color: rgb(34, 36, 44);\n"
                          "}\n"
                          "\n"
                          "#userNameEdit:hover, #emaildEdit:hover, #passwordEdit:hover, "
                          "#repeatPasswordEdit:hover {\n"
                          "	border: 2px solid rgb(85, 170, 255);\n"
                          "	background-color: rgb(43, 45, 56);\n"
                          "}\n"
                          "\n"
                          "#loginLabel {\n"
                          "	color: #999;\n"
                          "	border: 0px;\n"
                          "}\n"
                          "\n"
                          "#loginLabel:hover {\n"
                          "	color: green;\n"
                          "}\n"
                          "\n"
                          "#regButton {\n"
                          "	border-style: solid;\n"
                          "	border-color: #9999aa;\n"
                          "	border-radius: 10px;\n"
                          "	color: white;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#regButton:enabled {\n"
                          "	color: white;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 0, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#regButton:pressed {\n"
                          "	color: #fffffe;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#regButton:hover:!pressed {\n"
                          "	color: #0c2f70;\n"
                          "	background-color: qlineargradient(spread: pad, x1:0.5, y1:0, x2:0.5, "
                          "y2:1, stop:0 rgba(0, 255, 255, 255), stop:1 rgba(100, 255, 255, 255));\n"
                          "}\n"
                          "\n"
                          "#regButton:disabled {\n"
                          "	color: #ffffff;\n"
                          "	background-color: #aaaaaa;\n"
                          "}"));

    // connections
    connect(regButton, &QPushButton::clicked, this, &RegWindow::regClickedSlot);
    connect(loginLabel, &QPushButton::clicked, this, &RegWindow::openAuthSignal);
}

RegWindow::~RegWindow() {
}
