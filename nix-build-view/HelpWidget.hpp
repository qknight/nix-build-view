#ifndef HELPWIDGET__HPP
#define HELPWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class HelpWidget : public Widget {
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    int type();
};

#endif //HELPWIDGET__HPP
