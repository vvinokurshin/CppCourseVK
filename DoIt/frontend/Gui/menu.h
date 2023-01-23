#pragma once

#include "main_interfaces.h"

class Menu : public QWidget, IDraw {
  public:
    Menu() = default;
    ~Menu() = default;

    virtual void Draw() override;

  private:
    void setStyles();

    // Size Constants
    const size_t Width = 200;
    const size_t minHeight = 500;
    const size_t maxHeight = 2000;

    const size_t minElementsWidth = 100;
    const size_t maxElementsWidth = Width;
    const size_t elementsHeight = 40;

    const size_t IconSize = 30;
};
