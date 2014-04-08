#ifndef STATUSWIDGET__HPP
#define STATUSWIDGET__HPP

#include "Widget.hpp"

class StatusWidget : public Widget {
  std::string render(int w, int h);
};

#endif