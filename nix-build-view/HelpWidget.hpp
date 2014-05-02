#ifndef HELPWIDGET__HPP
#define HELPWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class HelpWidget : public Widget {
    AdvancedStringContainer render();
    int type();
};

#endif //HELPWIDGET__HPP
