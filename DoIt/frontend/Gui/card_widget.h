#pragma once

#include <QDateTimeEdit>
#include <QDialog>
#include <QObject>

#include "comment.h"
#include "main_interfaces.h"
#include "update.h"

#include <iostream>

#include "card.h"

class CardWidget : public QTextEdit, IDraw, IText {
    Q_OBJECT
  public:
    CardWidget(size_t _ID, size_t _columnID);

    CardWidget(size_t _ID, size_t _columnID, QString _title);

    CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption);

    CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QVector<QString> _tags);

    CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QString _deadline);

    CardWidget(size_t _ID, size_t _columnID, QString _title, QString _caption, QVector<QString> _tags,
               QString _deadline);

    ~CardWidget() = default;

    virtual void SetText(const QString& _title) override;

    virtual QString GetText() const override;

    void setCaption(const QString& _caption);

    QString getCaption() const;

    void addTags(QVector<QString> _tags);

    QVector<QString> getTags() const;

    size_t tagsCount() const;

    void addToHistory(Update _update);

    QVector<Update> getHistory() const;

    void setDeadline(const QString& _deadline);

    QString getDeadline() const;

    void addComment(Comment _comment);

    void deleteComment(Comment _comment);

    QVector<Comment> getComments() const;

    void setID(const int& _ID);

    int getID() const;

    int getColID() const {
        return columnID;
    }

    friend bool operator==(const CardWidget& l, const CardWidget& r);

    void Draw() override;

    void mouseReleaseEvent(QMouseEvent* event) override;

  signals:

    void sSignal();

  private:
    void setStyles();

    size_t ID;
    size_t columnID;

    QString title;
    QString caption;
    QVector<QString> tags;
    QString deadline;
    QVector<Comment> comments;

    // Size Constants
    const size_t Width = 230;  // Equal to column width
    const size_t Height = 60;
};

class CardWindow : public QDialog {
    Q_OBJECT

  public:
    CardWindow(CardWidget* _card, QWidget* parent = nullptr);

    CardWindow(QWidget* parent = nullptr) {
    }

    ~CardWindow();

  public slots:

    void deleteCardSlot() {
        delObjectSignal(card->getID(), CARD);
        flag = false;
        close();
    }

    void closeEvent(QCloseEvent*) override {
        std::cout << "closeEvent\n";
        if (flag) {
            Card c;
            c.id = card->getID();
            c.name = findChild<QLineEdit*>("cardNameEdit")->text().toStdString();
            c.caption = "";
            c.columnId = card->getColID();
            updateObjectSignal(c, CARD);
        }
    }

  signals:

    void delObjectSignal(size_t, ObjType);

    void updateObjectSignal(Object& obj, ObjType);

  private:
    CardWidget* card;
    bool flag = true;
};
