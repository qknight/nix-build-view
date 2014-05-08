#ifndef STATUSWIDGET__HPP
#define STATUSWIDGET__HPP

#include "Widget.hpp"

class StatusWidget : public Widget {
    AdvancedStringContainer render(unsigned int width, unsigned int height);
public:
    void setFocus(int arg1);
    int type();
private:
    unsigned int m_focus = 1;
};

#endif
