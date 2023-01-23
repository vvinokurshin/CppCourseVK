#pragma once

#include <iostream>

#include "board.h"
#include "boardwidgetmanager.h"
#include "menu.h"
#include "navbar.h"

#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>

class MainWindow : public QMainWindow, IDraw {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);

    ~MainWindow();

    void Draw() override;

    void showBoard(const Board& board) {
    }

    void showBoards(const std::vector<Board>& boards) {
        foreach (BoardWidget* bw, boardManager.getBoardWidgets()) {
            delete bw;
        }
        boardManager.clear();

        for (auto& board : boards) {
            BoardWidget* boardW = new BoardWidget(board.id, QString(board.name.data()));
            for (auto& column : board.columns) {
                ColumnWidget* columnW = new ColumnWidget(column.id, QString(column.name.data()));
                for (auto& card : column.cards) {
                    CardWidget* cardW = new CardWidget(card.id, column.id, QString(card.name.data()),
                                                       QString(card.caption.data()));
                    columnW->addCardWidget(cardW);
                }
                boardW->addColumnWidget(columnW);
            }
            boardManager.addBoardWidget(boardW);
        }

        QHBoxLayout* mainLayout = findChild<QHBoxLayout*>("mainLayout");

        QVector<BoardWidget*> boardWidgets = boardManager.getBoardWidgets();
        for (int i = 0; i < boardWidgets.size(); ++i) {
            boardWidgets[i]->Draw();
            if (i == curBoardIndex) {
                mainLayout->addWidget(boardWidgets[i], Qt::AlignLeft);
                continue;
            }

            boardWidgets[i]->hide();
            mainLayout->addWidget(boardWidgets[i], Qt::AlignLeft);
        }
        BoardWidget* boardW = boardManager.getBoardWidgets()[curBoardIndex];

        // connections
        QVector<QPushButton*> addCardLabels = boardW->findChildren<QPushButton*>("addCardButton");

        for (auto columnW : boardW->getColumnWidgets()) {
            for (auto cardW : columnW->getCardWidgets()) {
                connect(cardW, &CardWidget::sSignal, [cardW, this] { onCardClicked(cardW); });
            }
        }

        auto it = addCardLabels.begin();
        for (auto columnW : boardW->getColumnWidgets()) {
            connect(*it, &QPushButton::clicked, [columnW, this] { onAddCardClicked(columnW->getID()); });
            ++it;
        }

        QVector<QPushButton*> deleteColumnBtns = boardW->findChildren<QPushButton*>("deleteColumn");
        auto itDelCol = deleteColumnBtns.begin();
        for (auto columnW : boardW->getColumnWidgets()) {
            connect(*itDelCol, &QPushButton::clicked,
                    [columnW, this] { onDelColumnClicked(columnW->getID()); });
            ++itDelCol;
        }

        QPushButton* addColLabel = boardW->findChild<QPushButton*>("addColumnButton");
        connect(addColLabel, &QPushButton::clicked, [boardW, this] { onAddColumnClicked(boardW->getID()); });

        // For Navbar //
        QComboBox* chooseBoard = findChild<QComboBox*>("chooseBoard");
        chooseBoard->clear();
        for (auto bW : boardManager.getBoardWidgets()) {
            chooseBoard->addItem(QIcon("Gui/resources/background/default_board.jpg"), bW->GetText());
        }
        chooseBoard->setIconSize(QSize(40, 40));
        chooseBoard->setCurrentIndex(curBoardIndex);

        connect(chooseBoard, &QComboBox::activated, this, &MainWindow::onBoardChanged);
        resize();
    }

    void showLoadAllData() {
        QHBoxLayout* mainLayout = findChild<QHBoxLayout*>("mainLayout");

        mainLayout->addWidget(curWidget);
    }

    void deleteLoad() {
        delete curWidget;
    }

    void resize();

  public slots:

    void onAddBoardClicked() {
        QString name = QInputDialog::getText(this, "Добавление доски", "Название");

        Board board;
        board.name = name.toStdString();

        curBoardIndex = boardManager.getBoardWidgets().size();
        addObjectSignal(board, BOARD);
    }

    void onDelBoardClicked() {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления доски", "Удалить текущую доску?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            BoardWidget* boardW = boardManager.getBoardWidgets()[curBoardIndex];
            curBoardIndex = 0;
            delObjectSignal(boardW->getID(), BOARD);
        }
    }

    void onAddCardClicked(int col_id) {
        QString name = QInputDialog::getText(this, "Добавление карточки", "Название");

        Card card;

        card.name = name.toStdString();
        card.columnId = col_id;

        addObjectSignal(card, CARD);
    }

    void onAddColumnClicked(int board_id) {
        QString name = QInputDialog::getText(this, "Добавление колонки", "Название");

        Column col;

        col.name = name.toStdString();
        col.boardId = board_id;

        addObjectSignal(col, COLUMN);
    }

    void onDelColumnClicked(size_t col_id) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение удаления колонки", "Удалить текущую колонку?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            delObjectSignal(col_id, COLUMN);
        }
    }

    void onCardClicked(CardWidget* cw) {
        emit onCardClickedSignal(cw);
    }

    void onBoardChanged(int index) {
        QHBoxLayout* mainLayout = findChild<QHBoxLayout*>("mainLayout");

        mainLayout->insertWidget(1, boardManager.getBoardWidgets()[curBoardIndex], Qt::AlignLeft);

        boardManager.getBoardWidgets()[curBoardIndex]->hide();
        boardManager.getBoardWidgets()[index]->show();
        curBoardIndex = index;

        resize();
        BoardWidget* curBoard = boardManager.getBoardWidgets()[curBoardIndex];
        QVector<QPushButton*> addCardLabels = curBoard->findChildren<QPushButton*>("addCardButton");

        for (auto columnW : curBoard->getColumnWidgets()) {
            for (auto cardW : columnW->getCardWidgets()) {
                connect(cardW, &CardWidget::sSignal, [cardW, this] { onCardClicked(cardW); });
            }
        }

        // connections
        auto it = addCardLabels.begin();
        for (auto columnW : curBoard->getColumnWidgets()) {
            connect(*it, &QPushButton::clicked, [columnW, this] { onAddCardClicked(columnW->getID()); });
            ++it;
        }

        QPushButton* addColLabel = curBoard->findChild<QPushButton*>("addColumnButton");
        connect(addColLabel, &QPushButton::clicked,
                [curBoard, this] { onAddColumnClicked(curBoard->getID()); });

        QVector<QPushButton*> deleteColumnBtns = curBoard->findChildren<QPushButton*>("deleteColumn");
        auto itDelCol = deleteColumnBtns.begin();
        for (auto columnW : curBoard->getColumnWidgets()) {
            connect(*itDelCol, &QPushButton::clicked,
                    [columnW, this] { onDelColumnClicked(columnW->getID()); });
            ++itDelCol;
        }
    }

  signals:

    void addObjectSignal(Object&, ObjType);

    void delObjectSignal(size_t, ObjType);

    void updateObjectSignal(Object&, ObjType);

    void onCardClickedSignal(CardWidget* cw);

    void showBoardSignal(int idx);

  private:
    Navbar* navbar;
    Menu* menu;
    BoardWidgetManager boardManager;

    int curBoardIndex = 0;
    QWidget* curWidget = new QLabel("Load Boards.....");

    void resizeEvent(QResizeEvent* event) override;

    void setStyles();
};
