#ifndef STATUSWIDGET__HPP
#define STATUSWIDGET__HPP

#include "Widget.hpp"

class StatusWidget : public Widget {
    AdvancedStringContainer render();
public:
    void setFocus(int arg1);

private:
    int m_focus = 1;
};

#endif
