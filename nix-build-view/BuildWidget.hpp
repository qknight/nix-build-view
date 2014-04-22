#ifndef BUILDWIDGET__HPP
#define BUILDWIDGET__HPP

#include "Widget.hpp"
#include <string>

class BuildWidget : public Widget {
public:
    BuildWidget(std::string name, std::string status);
    AdvancedStringContainer render();
    int type();
private:
    std::string m_name;
    std::string m_status;
};

#endif
