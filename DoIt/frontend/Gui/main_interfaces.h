#pragma once

#include <QComboBox>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QTextEdit>
#include <QTime>
#include <QVBoxLayout>
#include <QWidget>

class IDraw {
  public:
    virtual ~IDraw() = default;

    virtual void Draw() = 0;
};

class IText {
  public:
    virtual ~IText() = default;

    virtual void SetText(const QString& _text) = 0;
    virtual QString GetText() const = 0;
};

class IDate {
  public:
    virtual ~IDate() = default;

    virtual void SetDate(QDateTime _date) = 0;
    virtual QDateTime GetDate() const = 0;
};
