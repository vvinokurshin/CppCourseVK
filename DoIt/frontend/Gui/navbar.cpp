#include "navbar.h"

void Navbar::Draw() {
    // Navbar //
    // QWidget *navbarWidget = new QWidget();
    setObjectName("navbarWidget");
    setMinimumSize(QSize(minWidth, Height));
    setMaximumSize(QSize(maxWidth, Height));
    setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* navbarLayout = new QHBoxLayout(this);
    navbarLayout->setObjectName("navbarLayout");
    navbarLayout->setContentsMargins(LefrRightMargins, 0, LefrRightMargins, 0);
    navbarLayout->setSpacing(0);
    // Navbar //

    // Content
    QLabel* programmIcon = new QLabel();
    programmIcon->setObjectName("programmIcon");
    programmIcon->setFixedSize(QSize(IconSize, IconSize));

    QLabel* programmName = new QLabel(QObject::tr("DoIT"));
    programmName->setObjectName("programmName");
    programmName->setFixedSize(QSize(programmNameWidth, elementsHeight));

    QComboBox* chooseBoard = new QComboBox();
    chooseBoard->setObjectName("chooseBoard");
    chooseBoard->setFixedSize(QSize(chooseBoardWidth, elementsHeight));
    chooseBoard->setCursor(QCursor(Qt::PointingHandCursor));

    QSpacerItem* spacer_1 =
        new QSpacerItem(spacerWidth, spacerHeight, QSizePolicy::Fixed, QSizePolicy::Minimum);

    QPushButton* createBoard = new QPushButton(QObject::tr("Создать"));
    createBoard->setObjectName("createBoard");
    createBoard->setFixedSize(QSize(createBoardWidth, elementsHeight));
    createBoard->setCursor(QCursor(Qt::PointingHandCursor));

    QPushButton* deleteBoard = new QPushButton(QObject::tr("Удалить"));
    deleteBoard->setObjectName("deleteBoard");
    deleteBoard->setFixedSize(QSize(createBoardWidth, elementsHeight));
    deleteBoard->setCursor(QCursor(Qt::PointingHandCursor));

    QSpacerItem* spacer_2 =
        new QSpacerItem(spacerWidth, spacerHeight, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QComboBox* userSettings = new QComboBox();
    userSettings->setObjectName("userSettings");
    userSettings->setFixedSize(QSize(IconSize, IconSize));
    userSettings->setCursor(QCursor(Qt::PointingHandCursor));

    // Add content
    navbarLayout->addWidget(programmIcon);
    navbarLayout->addWidget(programmName);
    navbarLayout->addWidget(chooseBoard);
    navbarLayout->addItem(spacer_1);
    navbarLayout->addWidget(createBoard);
    navbarLayout->addItem(spacer_1);
    navbarLayout->addWidget(deleteBoard);
    navbarLayout->addItem(spacer_2);
    navbarLayout->addWidget(userSettings);

    // Styles //
    setStyles();
}

void Navbar::setStyles() {
    setStyleSheet(
        QString::fromUtf8("#programmIcon {\n"
                          "	image: url(Gui/resources/icons/logo.jpg);\n"
                          "	width: 20px;\n"
                          "	min-height: 20px;\n"
                          "}\n"
                          "\n"
                          "#programmName {\n"
                          "	font: bold 24px;\n"
                          "	font-style: italic;\n"
                          "\n"
                          "	margin-right: 30px;\n"
                          "}\n"
                          "\n"
                          "#navbarWidget {\n"
                          "	background-color: hsl(194, 17%, 30.9%);\n"
                          "	margin: 0px 0px;\n"
                          "}\n"
                          "\n"
                          "#navbarWidget > * {\n"
                          "   border-radius: 5px;\n"
                          "	color: black;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard {\n"
                          "	background: transparent;\n"
                          "	padding-left: 5px;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard:hover {\n"
                          "	background-color: hsl(194, 4%, 53%);\n"
                          "}\n"
                          "\n"
                          "#chooseBoard::drop-down {\n"
                          "   subcontrol-origin: padding;\n"
                          "   subcontrol-position: top right;\n"
                          "\n"
                          "   border-top-right-radius: 5px;\n"
                          "   border-bottom-right-radius: 5px;\n"
                          "\n"
                          "	padding-right: 10px;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard::down-arrow {\n"
                          "   image: url(Gui/resources/icons/arrow.png);\n"
                          "	width: 20px;\n"
                          "	min-height: 20px;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard::down-arrow:on {\n"
                          "   top: 2px;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard QListView {\n"
                          "	padding: 5px;\n"
                          "	background-color: white;\n"
                          "   border-radius: 5px;\n"
                          "   outline: 0px;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard QListView::item {\n"
                          "   height: 30px;\n"
                          "	color: black;\n"
                          "}\n"
                          "\n"
                          "#chooseBoard QListView::item:focus, #chooseBoard QListView::item:hover, "
                          "#chooseBoard QListView::item:selected {\n"
                          "	background-color: silver;\n"
                          "	color: black;\n"
                          "}\n"
                          "\n"
                          "#createBoard, #deleteBoard {\n"
                          "	background-color:  hsl(194, 4%, 53%);\n"
                          "}\n"
                          "\n"
                          "#createBoard:hover, #deleteBoard:hover {\n"
                          "	background-color: hsl(194, 10%, 60%);\n"
                          "}\n"
                          "\n"
                          "#userSettings {\n"
                          "	background: transparent;\n"
                          "	image: url(Gui/resources/icons/default_user.png);\n"
                          "}\n"
                          "\n"
                          "#userSettings::drop-down {\n"
                          "	border: 0px;\n"
                          "}\n"
                          "\n"
                          "#userSettings QListView {\n"
                          "	min-width: 100px;\n"
                          "	background-color: white;\n"
                          "}\n"
                          "\n"
                          "#userSettings QListView::item {\n"
                          "	width: 100px;\n"
                          "   height: 30px;\n"
                          "}\n"
                          "\n"
                          "#userSettings QListView::item:focus, #userSettings QListView::item:hover {\n"
                          "	color: black;\n"
                          "	background-color: silver;\n"
                          "}\n"
                          ""));
}
