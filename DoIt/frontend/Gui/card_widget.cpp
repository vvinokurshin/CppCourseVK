#include "card_widget.h"

CardWidget::CardWidget(size_t _ID, size_t _columnID)
    : ID(_ID), columnID(_columnID), title(""), caption(""), tags(nullptr), deadline(""),
      comments(QVector<Comment>()) {
}

CardWidget::CardWidget(size_t _ID, size_t _columnID, QString _title)
    : ID(_ID), columnID(_columnID), title(_title), caption(""), tags(nullptr), deadline(""),
      comments(QVector<Comment>()) {
}

CardWidget::CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption)
    : ID(_ID), columnID(_columnID), title(_title), caption(_caption), tags(nullptr), deadline(""),
      comments(QVector<Comment>()) {
}

CardWidget::CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QVector<QString> _tags)
    : ID(_ID), columnID(_columnID), title(_title), caption(_caption), tags(_tags), deadline(""),
      comments(QVector<Comment>()) {
}

CardWidget::CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QString _deadline)
    : ID(_ID), columnID(_columnID), title(_title), caption(_caption), tags(nullptr), deadline(_deadline),
      comments(QVector<Comment>()) {
}

CardWidget::CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QVector<QString> _tags,
                       QString _deadline)
    : ID(_ID), columnID(_columnID), title(_title), caption(_caption), tags(_tags), deadline(_deadline),
      comments(QVector<Comment>()) {
}

void CardWidget::SetText(const QString& _title) {
    title = _title;
}

QString CardWidget::GetText() const {
    return title;
}

void CardWidget::setCaption(const QString& _caption) {
    caption = _caption;
}

QString CardWidget::getCaption() const {
    return caption;
}

void CardWidget::addTags(QVector<QString> _tags) {
    tags.append(_tags);
}

QVector<QString> CardWidget::getTags() const {
    return tags;
}

size_t CardWidget::tagsCount() const {
    return tags.size();
}

void CardWidget::setDeadline(const QString& _deadline) {
    deadline = _deadline;
}

QString CardWidget::getDeadline() const {
    return deadline;
}

void CardWidget::setID(const int& _ID) {
    ID = _ID;
}

int CardWidget::getID() const {
    return ID;
}

bool operator==(const CardWidget& l, const CardWidget& r) {
    if (l.title == r.title && l.caption == r.caption && l.deadline == r.deadline)
        return true;

    return false;
}

void CardWidget::Draw() {
    setObjectName("textEdit");
    setFixedSize(QSize(Width, Height));
    setText(title);

    setReadOnly(true);
    viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));

    // Styles
    setStyles();
}

void CardWidget::mouseReleaseEvent(QMouseEvent* event) {
    sSignal();
}

void CardWidget::setStyles() {
    this->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
                                          "   border-radius: 8px;\n"
                                          "	background-color: white;\n"
                                          "}\n"
                                          "\n"
                                          "QTextEdit:hover {\n"
                                          "	background-color: rgb(219, 220, 225);\n"
                                          "}\n"
                                          ""));
}

CardWindow::CardWindow(CardWidget* _card, QWidget* parent): card(_card), QDialog(parent) {
    setWindowTitle(_card->GetText());

    // Spacer
    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QSpacerItem* spacerExpanding = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* spacerFixed = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Central
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setFixedSize(QSize(800, 600));
    centralWidget->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* centralLayout = new QHBoxLayout(centralWidget);
    centralLayout->setObjectName("centralLayout");
    centralLayout->setContentsMargins(10, 10, 10, 0);
    centralLayout->setSpacing(10);

    // Left
    QWidget* leftWidget = new QWidget();
    leftWidget->setObjectName("leftWidget");
    leftWidget->setFixedSize(QSize(570, 600));
    leftWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setObjectName("leftLayout");
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setSpacing(10);

    // Left content
    // Card name
    QLineEdit* cardNameEdit = new QLineEdit();
    cardNameEdit->setObjectName("cardNameEdit");
    cardNameEdit->setMinimumSize(QSize(200, 40));
    cardNameEdit->setMaximumSize(QSize(600, 40));
    cardNameEdit->setText(_card->GetText());
    cardNameEdit->setCursor(QCursor(Qt::PointingHandCursor));

    // Column name
    QLabel* columnName = new QLabel("В колонке ");
    columnName->setObjectName("columnName");
    columnName->setMinimumSize(QSize(200, 30));
    columnName->setMaximumSize(QSize(600, 30));

    // Add to leftLayout
    leftLayout->addWidget(cardNameEdit);
    leftLayout->addWidget(columnName);

    // Deadline
    if (_card->getDeadline() != "") {
        QWidget* deadlineWidget = new QWidget();
        deadlineWidget->setObjectName("deadlineWidget");
        deadlineWidget->setMinimumSize(QSize(200, 50));
        deadlineWidget->setMaximumSize(QSize(600, 50));
        deadlineWidget->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout* deadlineLayout = new QHBoxLayout(deadlineWidget);
        deadlineLayout->setSpacing(10);
        deadlineLayout->setObjectName("deadlineLayout");

        QLabel* deadlineLabel = new QLabel(QObject::tr("Срок"));
        deadlineLabel->setObjectName("deadlineLabel");
        deadlineLabel->setFixedSize(QSize(100, 40));
        deadlineLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

        // Deadline edit
        QDateTimeEdit* deadlineEdit = new QDateTimeEdit();
        deadlineEdit->setObjectName("deadlineEdit");
        deadlineEdit->setFixedSize(QSize(200, 30));
        deadlineEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        deadlineEdit->setCalendarPopup(true);
        deadlineEdit->setDateTime(QDateTime::fromString(_card->getDeadline(), "dd.MM.yyyy H:mm"));
        deadlineEdit->setCursor(QCursor(Qt::PointingHandCursor));

        // Add to deadlineLayout
        deadlineLayout->addWidget(deadlineLabel);
        deadlineLayout->addItem(spacer);
        deadlineLayout->addWidget(deadlineEdit);
        deadlineLayout->addItem(spacer);

        // Add to leftLayout
        leftLayout->addWidget(deadlineWidget);
    }

    // Tags
    if (_card->tagsCount() != 0) {
        QWidget* tagsWidget = new QWidget();
        tagsWidget->setObjectName("tagsWidget");
        tagsWidget->setMinimumSize(QSize(200, 50));
        tagsWidget->setMaximumSize(QSize(600, 50));
        tagsWidget->setContentsMargins(0, 0, 0, 0);

        QHBoxLayout* tagsLayout = new QHBoxLayout();
        tagsLayout->setObjectName("tagsLayout");
        tagsLayout->setContentsMargins(0, 0, 0, 0);
        tagsLayout->setSpacing(10);

        QLabel* tagsLabel = new QLabel(QObject::tr("Метки"));
        tagsLabel->setObjectName("tagsLabel");
        tagsLabel->setFixedSize(QSize(100, 40));
        tagsLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

        // Add to tagsLayout
        tagsLayout->addWidget(tagsLabel);
        tagsLayout->addItem(spacer);

        foreach (QString strTag, _card->getTags()) {
            QLabel* tagLabel = new QLabel(strTag);
            tagLabel->setObjectName("tagLabel");
            tagLabel->setMinimumSize(QSize(50, 40));
            tagLabel->setMaximumSize(QSize(200, 40));
            tagLabel->setCursor(QCursor(Qt::PointingHandCursor));

            tagsLayout->addWidget(tagLabel);
        }

        tagsLayout->addItem(spacer);

        // Add to leftLayout
        leftLayout->addWidget(tagsWidget);
    }

    // Add to leftLayout
    leftLayout->addItem(spacerExpanding);

    // Right
    QWidget* rightWidget = new QWidget();
    rightWidget->setObjectName("rightWidget");
    rightWidget->setFixedSize(QSize(200, 600));
    rightWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setObjectName("rightLayout");
    rightLayout->setSpacing(5);
    rightLayout->setContentsMargins(5, 0, 5, 0);

    // Right content
    // Add to card label
    QLabel* addToCardLabel = new QLabel(QObject::tr("Добавить на карточку"));
    addToCardLabel->setObjectName("addToCardLabel");
    addToCardLabel->setFixedSize(QSize(190, 40));

    // Add tag button
    QPushButton* addTagButton = new QPushButton(QObject::tr("Тег"));
    addTagButton->setObjectName("addTagButton");
    addTagButton->setFixedSize(QSize(190, 40));
    addTagButton->setCursor(QCursor(Qt::PointingHandCursor));

    // Add deadline button
    QPushButton* addDeadlineButton = new QPushButton(QObject::tr("Дедлайн"));
    addDeadlineButton->setObjectName("addDeadlineButton");
    addDeadlineButton->setFixedSize(QSize(190, 40));
    addDeadlineButton->setCursor(QCursor(Qt::PointingHandCursor));

    if (_card->getDeadline() != "") {
        addDeadlineButton->setDisabled(true);
    }

    // Line
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);  // Horizontal line
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);

    // Actions label
    QLabel* actionsLabel = new QLabel(QObject::tr("Действия"));
    actionsLabel->setObjectName("actionsLabel");
    actionsLabel->setFixedSize(QSize(190, 40));

    // Move card button
    QPushButton* moveCardButton = new QPushButton(QObject::tr("Переместить"));
    moveCardButton->setObjectName("moveCardButton");
    moveCardButton->setFixedSize(QSize(190, 40));
    moveCardButton->setCursor(QCursor(Qt::PointingHandCursor));

    // Delete card button
    QPushButton* deleteCardButton = new QPushButton(QObject::tr("Удалить"));
    deleteCardButton->setObjectName("deleteCardButton");
    deleteCardButton->setFixedSize(QSize(190, 40));
    deleteCardButton->setCursor(QCursor(Qt::PointingHandCursor));

    // Add to rightLayout
    rightLayout->addWidget(deleteCardButton);
    rightLayout->addWidget(line);
    rightLayout->addWidget(addToCardLabel);
    rightLayout->addWidget(addTagButton);
    addTagButton->setDisabled(true);
    rightLayout->addWidget(addDeadlineButton);
    addDeadlineButton->setDisabled(true);
    rightLayout->addItem(spacerFixed);
    rightLayout->addWidget(actionsLabel);
    rightLayout->addWidget(moveCardButton);
    moveCardButton->setDisabled(true);
    rightLayout->addItem(spacerExpanding);

    // Add to centralLayout
    centralLayout->addWidget(leftWidget);
    centralLayout->addWidget(rightWidget);

    // Styles //
    setStyleSheet(QString::fromUtf8(
        "* {\n"
        "  	font-family: \"Times New Roman\", Times, serif;\n"
        " 	font-size: 16px;\n"
        "  	font-weight: Normal;\n"
        "}\n"
        "\n"
        "#centralWidget {\n"
        "	background-color: rgb(244, 245, 247);\n"
        "}\n"
        "\n"
        "#cardNameEdit {\n"
        "	color: black;\n"
        "	border-radius: 10px;\n"
        "	background: transparent;\n"
        "	padding-left: 5px;\n"
        "	font-size: 20px;\n"
        "}\n"
        "\n"
        "#cardNameEdit:focus {\n"
        "	border: 1px solid blue;\n"
        "	background-color: white;\n"
        "}\n"
        "\n"
        "#columnName, #deadlineLabel, #tagsLabel, #addToCardLabel, #actionsLabel {\n"
        "	color: grey;\n"
        "}\n"
        "\n"
        "#tagLabel {\n"
        "	background-color: rgb(215, 237, 211);\n"
        "	border-radius: 5px;\n"
        "	padding: 5px 0px;\n"
        "}\n"
        "\n"
        "#tagLabel:hover {\n"
        "	background-color: rgb(185, 201, 182);\n"
        "}\n"
        "\n"
        "#addTagButton, #addDeadlineButton, #moveCardButton, #deleteCardButton {\n"
        "	background-color: rgb(235, 237, 240);\n"
        "	border-radius: 5px;\n"
        "	border: 0px;\n"
        "}\n"
        "\n"
        "#addTagButton:hover, #addDeadlineButton:hover, #moveCardButton:hover, #deleteCardButton"
        ":hover {\n"
        "	background-color: rgb(227, 229, 234);\n"
        "}\n"
        ""));

    connect(deleteCardButton, &QPushButton::clicked, this, &CardWindow::deleteCardSlot);
}

CardWindow::~CardWindow() {
}
