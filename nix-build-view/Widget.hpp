#ifndef WIDGET__HPP
#define WIDGET__HPP

#include "WindowManager.hpp"
#include "AdvancedString.hpp"

namespace WidgetName {
enum {
    HelpWidget,
    TerminalWidget,
    UrlWidgetManager,
    UrlWidget,
    BuildWidgetManager,
    BuildWidget,
    StatusWidget
};
};

class Widget {
public:
    virtual AdvancedStringContainer render(unsigned int width, unsigned int height) = 0;
    void update() {
        WindowManager::Instance()->update(this);
    }
    unsigned int width()  {
        return m_width;
    }
    unsigned int height() {
        return m_height;
    }
    void hide() {
        m_visible = false;
    }
    void show() {
        m_visible = true;
    }
    virtual int type() = 0;
    void keyboardInputHandler(int ch);
    unsigned int m_width = 0;
    unsigned int m_height = 0;
private:
    bool m_visible = true;
};

#endif
