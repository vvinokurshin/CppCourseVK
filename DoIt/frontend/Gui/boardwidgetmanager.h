#pragma once

#include "board_widget.h"

class BoardWidgetManager {
  public:
    BoardWidgetManager() = default;

    BoardWidgetManager(QVector<BoardWidget*> _boardWidget);

    ~BoardWidgetManager() = default;

    void addBoardWidget(BoardWidget* _boardWidget);

    void deleteBoardWidget(BoardWidget* _boardWidget);

    QVector<BoardWidget*> getBoardWidgets();

    BoardWidget* getBoardWidget(size_t _ID);

    BoardWidget* first() const;

    BoardWidget* last() const;

    void clear() {
        boardWidgets.clear();
    }

    size_t boardsCount();

  private:
    QVector<BoardWidget*> boardWidgets;
};
