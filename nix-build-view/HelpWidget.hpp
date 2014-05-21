#ifndef HELPWIDGET__HPP
#define HELPWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class HelpWidget : public Widget {
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    int type();
private:
      unsigned int width() {
        return m_width;
    }
    unsigned int height() {
        return m_height;
    }
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    std::vector<AdvancedStringContainer> m_terminal;
};

#endif //HELPWIDGET__HPP
