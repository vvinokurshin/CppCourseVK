#include "boardwidgetmanager.h"

BoardWidgetManager::BoardWidgetManager(QVector<BoardWidget*> _boardWidget): boardWidgets(_boardWidget) {
}

void BoardWidgetManager::addBoardWidget(BoardWidget* _boardWidget) {
    boardWidgets.append(_boardWidget);
}

void BoardWidgetManager::deleteBoardWidget(BoardWidget* _boardWidget) {
    boardWidgets.removeOne(_boardWidget);
}

QVector<BoardWidget*> BoardWidgetManager::getBoardWidgets() {
    return boardWidgets;
}

BoardWidget* BoardWidgetManager::getBoardWidget(size_t _ID) {
    foreach (BoardWidget* boardWidget, boardWidgets) {
        if (boardWidget->getID() == _ID)
            return boardWidget;
    }

    return nullptr;
}

BoardWidget* BoardWidgetManager::first() const {
    return boardWidgets.first();
}

BoardWidget* BoardWidgetManager::last() const {
    return boardWidgets.last();
}

size_t BoardWidgetManager::boardsCount() {
    return boardWidgets.size();
}
