#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent) {
    navbar = new Navbar();
    menu = new Menu();

    // Draw
    Draw();

    QStringList settings;
    QComboBox* userSettings = findChild<QComboBox*>("userSettings");
    settings << tr("Профиль") << tr("Помощь") << tr("Выйти");

    for (int i = 0, sep = 1; i < settings.size(); ++i) {
        userSettings->addItem(settings[i]);
        userSettings->insertSeparator(sep);
        sep += 2;
    }

    userSettings->setCurrentIndex(-1);  // Не забыть сбрасывать при изменении

    QPushButton* createBoard = findChild<QPushButton*>("createBoard");
    QPushButton* deleteBoard = findChild<QPushButton*>("deleteBoard");
    connect(createBoard, &QPushButton::clicked, this, &MainWindow::onAddBoardClicked);
    connect(deleteBoard, &QPushButton::clicked, this, &MainWindow::onDelBoardClicked);
}

MainWindow::~MainWindow() {
}

void MainWindow::Draw() {
    // Central //
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setObjectName("centralLayout");
    centralLayout->setContentsMargins(0, 0, 0, 0);
    centralLayout->setSpacing(0);

    // Main //
    QWidget* mainWidget = new QWidget();
    mainWidget->setObjectName("mainWidget");
    mainWidget->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* mainLayout = new QHBoxLayout(mainWidget);
    mainLayout->setObjectName("mainLayout");
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Add Navbar and Main //
    navbar->Draw();
    centralLayout->addWidget(navbar);
    centralLayout->addWidget(mainWidget);

    // Add to Main Layout
    menu->Draw();
    mainLayout->addWidget(menu, Qt::AlignLeft);
    //    mainLayout->addWidget(curWidget, Qt::AlignLeft);

    setCentralWidget(centralWidget);

    // Styles //
    setStyles();
}

void MainWindow::setStyles() {
    setStyleSheet(QString::fromUtf8("* {\n"
                                    "  font-family: \"Times New Roman\", Times, serif;\n"
                                    "  font-size: 16px;\n"
                                    "  font-weight: Normal;\n"
                                    "}\n"
                                    ""));
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    resize();
}

void MainWindow::resize() {
    std::cout << "resize" << std::endl;
    // For Scroll Columns //
    QWidget* centralWidget = findChild<QWidget*>("centralWidget");
    QWidget* navbarWidget = findChild<QWidget*>("navbarWidget");
    QWidget* menuWidget = findChild<QWidget*>("menuWidget");

    QVector<QWidget*> headerBoardWidgets = findChildren<QWidget*>("headerBoardWidget");

    QVector<QScrollArea*> scrollAreaBoards = findChildren<QScrollArea*>("scrollAreaBoard");

    for (int i = 0; i < scrollAreaBoards.size(); ++i) {
        int height = centralWidget->size().height() - navbarWidget->size().height() -
                     headerBoardWidgets[i]->size().height();
        int width = centralWidget->size().width() - menuWidget->size().width();

        scrollAreaBoards[i]->resize(width, height);

        // For Each Column Size //
        QVector<QWidget*> columnWidgets = findChildren<QWidget*>("columnWidget");

        foreach (QWidget* columnWidget, columnWidgets) {
            QVBoxLayout* columnLayout = columnWidget->findChild<QVBoxLayout*>("columnLayout");
            QVBoxLayout* cardsLayout = columnWidget->findChild<QVBoxLayout*>("cardsLayout");
            QScrollArea* scrollAreaCards = columnWidget->findChild<QScrollArea*>("scrollAreaCards");
            QPushButton* addCardButton = columnWidget->findChild<QPushButton*>("addCardButton");

            int *left = new int, *top = new int, *right = new int, *bottom = new int;
            columnLayout->getContentsMargins(left, top, right, bottom);
            size_t bottomSpace = 20;

            if (cardsLayout->sizeHint().height() > scrollAreaCards->size().height() ||
                columnWidget->size().height() > height - bottomSpace) {
                if (height != cardsLayout->sizeHint().height()) {

                    columnWidget->setFixedSize(columnWidget->size().width(), height - bottomSpace);

                    scrollAreaCards->setFixedSize(columnWidget->size().width() - *left - *right,
                                                  height - 80 - addCardButton->size().height());
                }
            }
        }
    }
}
