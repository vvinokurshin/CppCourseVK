#pragma once

#include "column_widget.h"

class BoardWidget : public QWidget, IText, IDraw {
  public:
    BoardWidget(size_t _ID);
    BoardWidget(size_t _ID, QString _name);
    BoardWidget(size_t _ID, QString _name, QVector<ColumnWidget*> _columns);
    BoardWidget(size_t _ID, QString _name, QVector<ColumnWidget*> _columns, QVector<UiUser> _users);
    ~BoardWidget() = default;

    virtual void SetText(const QString& _name) override;
    virtual QString GetText() const override;

    void addColumnWidget(ColumnWidget* _column);
    void deleteColumnWidget(ColumnWidget* _column);
    void swapColumnWidgets(const int& first, const int& second);

    QVector<ColumnWidget*> getColumnWidgets();

    void setUsers(QVector<UiUser> _users);
    QVector<UiUser> getUsers() const;

    void addToHistory(Update _update);
    QVector<Update> getHistory() const;

    int getID() const;

    int columnCount() const;

    void Draw() override;

  private:
    size_t ID;
    QString name;
    QVector<ColumnWidget*> columnWidgets;
    QVector<UiUser> users;
    QVector<Update> history;
    // image

    // Size Constants
    const size_t minWidth = 600;
    const size_t minHeight = 500;

    const size_t elementsHeight = 30;

    const size_t minHeaderWidth = minWidth;
    const size_t maxHeaderWidth = 2000;
    const size_t headerHeight = 40;

    const size_t minBoardNameWidth = 200;
    const size_t maxBoardNameWidth = 300;

    const size_t addUsersWidth = 200;

    const size_t addColumnButtonWidth = 250;
    const size_t addColumnButtonHeight = 40;

    const size_t mediumIconSize = 20;
};
