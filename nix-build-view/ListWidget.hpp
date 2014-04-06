#ifndef LISTWIDGET__HPP
#define LISTWIDGET__HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "Widget.hpp"


class ListWidget : public Widget {
public:
    std::string render(int w, int h);
    void append(std::string line);
private:
  std::stringstream m_logfile;
};

#endif