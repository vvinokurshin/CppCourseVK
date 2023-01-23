#include "menu.h"

void Menu::Draw() {
    // Menu //
    setObjectName("menuWidget");
    setMinimumSize(QSize(Width, minHeight));
    setMaximumSize(QSize(Width, maxHeight));
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* menuLayout = new QVBoxLayout(this);
    menuLayout->setObjectName("menuLayout");
    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);
    // Menu //

    // Row 1
    QWidget* rowWidget_1 = new QWidget();
    rowWidget_1->setObjectName("rowWidget_1");
    rowWidget_1->setMinimumSize(QSize(minElementsWidth, elementsHeight));
    rowWidget_1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* rowLayout_1 = new QHBoxLayout(rowWidget_1);
    rowLayout_1->setObjectName("rowLayout_1");
    rowLayout_1->setContentsMargins(0, 0, 0, 0);
    rowLayout_1->setSpacing(0);

    // Row 1 Content
    QLabel* actionsText = new QLabel(QObject::tr("Действия"));
    actionsText->setObjectName("actionsText");
    actionsText->setMinimumSize(QSize(minElementsWidth, elementsHeight));
    actionsText->setAlignment(Qt::AlignCenter);

    // Add
    rowLayout_1->addWidget(actionsText);

    // Line
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);  // Horizontal line
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);

    // Row 2
    QWidget* rowWidget_2 = new QWidget();
    rowWidget_2->setObjectName("rowWidget_2");
    rowWidget_2->setMinimumSize(QSize(minElementsWidth, elementsHeight));
    rowWidget_2->setCursor(QCursor(Qt::PointingHandCursor));
    rowWidget_2->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* rowLayout_2 = new QHBoxLayout(rowWidget_2);
    rowLayout_2->setObjectName("rowLayout_2");
    rowLayout_2->setContentsMargins(0, 0, 0, 0);
    rowLayout_2->setSpacing(0);

    // Row 2 Content
    QLabel* avatarIcon = new QLabel();
    avatarIcon->setObjectName("avatarIcon");
    avatarIcon->setFixedSize(QSize(IconSize, IconSize));
    avatarIcon->setCursor(QCursor(Qt::PointingHandCursor));

    QLabel* usersText = new QLabel(QObject::tr("Участники"));
    usersText->setObjectName("usersText");
    usersText->setMinimumSize(QSize(minElementsWidth, elementsHeight));
    usersText->setMaximumSize(QSize(maxElementsWidth, elementsHeight));
    usersText->setCursor(QCursor(Qt::PointingHandCursor));

    QLabel* addAvatarIcon = new QLabel();
    addAvatarIcon->setObjectName("addAvatarIcon");
    addAvatarIcon->setFixedSize(QSize(IconSize, IconSize));
    addAvatarIcon->setCursor(QCursor(Qt::PointingHandCursor));

    // Add
    rowLayout_2->addWidget(avatarIcon);
    rowLayout_2->addWidget(usersText);
    rowLayout_2->addWidget(addAvatarIcon);

    // Spacer at the end
    QSpacerItem* bMenuSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Add
    menuLayout->addWidget(rowWidget_1);
    menuLayout->addWidget(line);
    menuLayout->addWidget(rowWidget_2);
    menuLayout->addItem(bMenuSpacer);

    // Styles //
    setStyles();
}

void Menu::setStyles() {
    setStyleSheet(QString::fromUtf8("#menuWidget {\n"
                                    "	background-color: hsla(194,17%,35.9%,0.9);\n"
                                    "}\n"
                                    "\n"
                                    "#menuWidget > * > * {\n"
                                    "	color: white;\n"
                                    "    border-radius: 5px;\n"
                                    "}\n"
                                    "\n"
                                    "#actionsText {\n"
                                    "	font: bold 18px;\n"
                                    "	font-style: italic;\n"
                                    "}\n"
                                    "\n"
                                    "#usersText {\n"
                                    "	font: bold 14px;\n"
                                    "	padding-left: 10px;\n"
                                    "}\n"
                                    "\n"
                                    "#avatarIcon {\n"
                                    "	background: transparent;\n"
                                    "	image: url(Gui/resources/icons/user_white.png);\n"
                                    "	margin-left: 5px;\n"
                                    "}\n"
                                    "\n"
                                    "#addAvatarIcon {\n"
                                    "	background: transparent;\n"
                                    "	image: url(Gui/resources/icons/plus_white.png);\n"
                                    "	margin-right: 10px;\n"
                                    "}\n"
                                    "\n"
                                    "#rowWidget_2:hover {\n"
                                    "	background-color: hsl(194, 4%, 53%);\n"
                                    "}\n"
                                    ""));
}
