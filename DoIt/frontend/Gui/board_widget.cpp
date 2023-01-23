#include "board_widget.h"

BoardWidget::BoardWidget(size_t _ID)
    : ID(_ID), name(""), columnWidgets(QVector<ColumnWidget*>()), users(QVector<UiUser>()),
      history(QVector<Update>()) {
}

BoardWidget::BoardWidget(size_t _ID, QString _name)
    : ID(_ID), name(_name), columnWidgets(QVector<ColumnWidget*>()), users(QVector<UiUser>()),
      history(QVector<Update>()) {
}

BoardWidget::BoardWidget(size_t _ID, QString _name, QVector<ColumnWidget*> _columnWidgets)
    : ID(_ID), name(_name), columnWidgets(_columnWidgets), users(QVector<UiUser>()),
      history(QVector<Update>()) {
}

BoardWidget::BoardWidget(size_t _ID, QString _name, QVector<ColumnWidget*> _columnWidgets,
                         QVector<UiUser> _users)
    : ID(_ID), name(_name), columnWidgets(_columnWidgets), users(_users), history(QVector<Update>()) {
}

void BoardWidget::SetText(const QString& _name) {
    name = _name;
}

QString BoardWidget::GetText() const {
    return name;
}

void BoardWidget::addColumnWidget(ColumnWidget* _columnWidget) {
    columnWidgets.append(_columnWidget);
}

void BoardWidget::deleteColumnWidget(ColumnWidget* _columnWidget) {
    columnWidgets.removeOne(_columnWidget);
}

void BoardWidget::swapColumnWidgets(const int& first, const int& second) {
    columnWidgets.swapItemsAt(first, second);
}

QVector<ColumnWidget*> BoardWidget::getColumnWidgets() {
    return columnWidgets;
}

void BoardWidget::setUsers(QVector<UiUser> _users) {
    users.append(_users);
}

QVector<UiUser> BoardWidget::getUsers() const {
    return users;
}

void BoardWidget::addToHistory(Update _update) {
    history.append(_update);
}

QVector<Update> BoardWidget::getHistory() const {
    return history;
}

int BoardWidget::getID() const {
    return ID;
}

int BoardWidget::columnCount() const {
    return columnWidgets.size();
}

bool operator==(const BoardWidget& l, const BoardWidget& r) {
    if (l.GetText() == r.GetText())
        return true;

    return false;
}

void BoardWidget::Draw() {
    // BoardWidget //
    setObjectName("BoardWidget");
    setMinimumSize(QSize(minWidth, minHeight));
    setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* BoardWidgetLayout = new QVBoxLayout(this);
    BoardWidgetLayout->setObjectName("BoardWidgetLayout");
    BoardWidgetLayout->setContentsMargins(0, 0, 0, 0);
    BoardWidgetLayout->setSpacing(0);
    // BoardWidget //

    // BoardWidget Header //
    QWidget* headerBoardWidget = new QWidget();
    headerBoardWidget->setObjectName("headerBoardWidget");
    headerBoardWidget->setMinimumSize(QSize(minHeaderWidth, headerHeight));
    headerBoardWidget->setMaximumSize(QSize(maxHeaderWidth, headerHeight));
    headerBoardWidget->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* headerBoardLayout = new QHBoxLayout(headerBoardWidget);
    headerBoardLayout->setObjectName("headerBoardLayout");
    headerBoardLayout->setContentsMargins(10, 0, 10, 0);

    // BoardWidget content //
    QLineEdit* currentBoardName = new QLineEdit();
    currentBoardName->setObjectName("currentBoardName");
    currentBoardName->setMinimumSize(QSize(minBoardNameWidth, elementsHeight));
    currentBoardName->setMaximumSize(QSize(maxBoardNameWidth, elementsHeight));
    currentBoardName->setText(name);
    currentBoardName->setCursor(QCursor(Qt::PointingHandCursor));

    QSpacerItem* bwSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Add
    headerBoardLayout->addWidget(currentBoardName);
    headerBoardLayout->addItem(bwSpacer);

    QHBoxLayout* usersLayout = new QHBoxLayout();
    usersLayout->setObjectName("usersLayout");
    usersLayout->setContentsMargins(0, 0, 0, 0);

    // Button to add users to BoardWidget
    QPushButton* addUsers = new QPushButton(QObject::tr("Добавить"));
    addUsers->setObjectName("addUsers");
    addUsers->setFixedSize(QSize(addUsersWidth, elementsHeight));
    addUsers->setCursor(QCursor(Qt::PointingHandCursor));
    addUsers->setIcon(QIcon("Gui/resources/icons/add_user.png"));

    // Add //
    headerBoardLayout->addLayout(usersLayout);
    headerBoardLayout->addWidget(addUsers);

    BoardWidgetLayout->addWidget(headerBoardWidget);

    // MainBoardWidget //
    QWidget* mainBoardWidget = new QWidget();
    mainBoardWidget->setObjectName("mainBoardWidget");
    mainBoardWidget->setMinimumSize(QSize(minWidth, minHeight));
    mainBoardWidget->setContentsMargins(0, 0, 0, 0);

    // Scroll for columns
    QScrollArea* scrollAreaBoard = new QScrollArea(mainBoardWidget);
    scrollAreaBoard->setObjectName("scrollAreaBoard");
    scrollAreaBoard->setContentsMargins(0, 0, 0, 0);
    scrollAreaBoard->setWidgetResizable(true);
    scrollAreaBoard->setFrameShape(QFrame::NoFrame);
    scrollAreaBoard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget* scrollAreaBoardContents = new QWidget(scrollAreaBoard);
    scrollAreaBoardContents->setObjectName("scrollAreaBoardContents");
    scrollAreaBoardContents->setContentsMargins(0, 0, 0, 0);

    // Layout in scroll
    QHBoxLayout* mainBoardLayout = new QHBoxLayout(scrollAreaBoardContents);
    mainBoardLayout->setObjectName("mainBoardLayout");
    mainBoardLayout->setContentsMargins(10, 0, 10, 0);
    mainBoardLayout->setSpacing(10);
    mainBoardLayout->setAlignment(Qt::AlignLeft);

    // Add columns //
    foreach (ColumnWidget* columnWidget, columnWidgets) {
        columnWidget->Draw();

        mainBoardLayout->addWidget(columnWidget);
        mainBoardLayout->setAlignment(columnWidget, Qt::AlignTop);
    }

    // Add extra column
    QPushButton* addColumnButton = new QPushButton(QObject::tr("Добавьте ещё одну колонку"));
    addColumnButton->setObjectName("addColumnButton");
    addColumnButton->setFixedSize(QSize(addColumnButtonWidth, addColumnButtonHeight));
    addColumnButton->setIcon(QIcon("Gui/resources/icons/plus_white.png"));

    // Add extra column to layout //
    mainBoardLayout->addWidget(addColumnButton);
    mainBoardLayout->setAlignment(addColumnButton, Qt::AlignTop);

    scrollAreaBoard->setWidget(scrollAreaBoardContents);

    BoardWidgetLayout->addWidget(mainBoardWidget);

    this->setStyleSheet(QString::fromUtf8(
        "#BoardWidget {\n"
        "	border-image: url(Gui/resources/background/default_board.jpg) 0 0 0 0 stretch stretch;\n"
        "}\n"
        "\n"
        "#headerBoardLayout {\n"
        "	background: transparent;\n"
        "}\n"
        "\n"
        "#headerBoardWidget > * {\n"
        "	color: white;\n"
        "}\n"
        "\n"
        "#currentBoardName {\n"
        "   background: transparent;\n"
        "   border: 0px;\n"
        "   border-radius: 5px;\n"
        "   padding-left: 5px;\n"
        "	font: bold 20px;\n"
        "}\n"
        "\n"
        "#currentBoardName:focus {\n"
        "	border: 1px solid blue;\n"
        "}\n"
        "\n"
        "#addUsers {\n"
        "	color: black;\n"
        "	background-color: white;\n"
        "	border-radius: 5px;\n"
        "	border: 1px solid silver;\n"
        "}\n"
        "\n"
        "#addUsers:hover {\n"
        "	color: black;\n"
        "	background-color: silver;\n"
        "}\n"
        "\n"
        "#mainBoardWidget {\n"
        "	background: transparent;\n"
        "}\n"
        "\n"
        "#scrollAreaBoard {\n"
        "	background: transparent;\n"
        "}\n"
        "\n"
        "#scrollAreaBoardContents {\n"
        "	background: transparent;\n"
        "}\n"
        "\n"
        "#addColumnButton {\n"
        "   background-color: rgba(120, 120, 120, 90);\n"
        "   border-radius: 5px;\n"
        "   color: #ffffff;\n"
        "   text-align: left;\n"
        "   padding-left: 10px;\n"
        "}\n"
        "\n"
        "#addColumnButton:hover {\n"
        "   background-color: rgba(120, 120, 120, 60);\n"
        "}\n"
        ""));
}
