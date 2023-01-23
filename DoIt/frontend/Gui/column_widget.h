#pragma once

#include "card_widget.h"

class ColumnWidget : public QWidget, IText, IDraw {
  public:
    ColumnWidget(size_t _ID);

    ColumnWidget(size_t _ID, QString _name);

    ColumnWidget(size_t _ID, QString _name, QVector<CardWidget*> _cardWidgets);

    ~ColumnWidget() = default;

    virtual void SetText(const QString& _name) override;

    virtual QString GetText() const override;

    void addCardWidget(CardWidget* _cardWidget);

    void deleteCardWidget(CardWidget* _cardWidget);

    void swapCardWidgets(const int& first, const int& second);

    QVector<CardWidget*> getCardWidgets();

    CardWidget* getCardWidget(size_t _ID);

    size_t getID() const;

    size_t cardsCount() const;

    friend bool operator==(const ColumnWidget& l, const ColumnWidget& r);

    void Draw() override;

    void mouseReleaseEvent(QMouseEvent* event) override;

  private:
    void setStyles();

    size_t ID;

    QString name;
    QVector<CardWidget*> cardWidgets;

    // Size Constants
    const size_t Width = 250;

    const size_t elementsWidth = 230;

    const size_t titleWidth = elementsWidth - mediumIconSize;
    const size_t titleHeight = 30;
    const size_t itemHeight = 30;

    const size_t mediumIconSize = 30;
};
