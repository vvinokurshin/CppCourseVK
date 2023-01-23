#pragma once

#include "main_interfaces.h"

class Navbar : public QWidget, IDraw {
  public:
    Navbar() = default;
    ~Navbar() = default;

    virtual void Draw() override;

  private:
    void setStyles();

    // Size Constants
    const size_t minWidth = 600;
    const size_t maxWidth = 3000;
    const size_t Height = 35;
    const size_t LefrRightMargins = 10;

    const size_t elementsHeight = 30;

    const size_t IconSize = 30;
    const size_t programmNameWidth = 100;
    const size_t chooseBoardWidth = 200;
    const size_t createBoardWidth = 100;

    const size_t spacerWidth = 20;
    const size_t spacerHeight = 20;
};
