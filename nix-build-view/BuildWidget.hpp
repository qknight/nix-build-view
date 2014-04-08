#ifndef BUILDWIDGET__HPP
#define BUILDWIDGET__HPP

#include "Widget.hpp"
#include <string>

class BuildWidget : public Widget {
public:
    BuildWidget(std::string name);
    std::string render(int w, int h);
private:
    std::string m_name;
};

#endif
