#ifndef WIDGET__HPP
#define WIDGET__HPP

#include "WindowManager.hpp"
#include "AdvancedString.hpp"

namespace WidgetName {
enum {
    HelpWidget,
    ListWidget,
    UrlWidgetManager,
    UrlWidget,
    BuildWidgetManager,
    BuildWidget,
    StatusWidget
};
};

class Widget {
public:
    virtual AdvancedStringContainer render() = 0;
    void update() {
        //FIXME tell the WM to update(this)!
        WindowManager::Instance()->update();
    };
    unsigned int width()  {
        return m_width;
    };
    unsigned int height() {
        return m_height;
    };
    void hide() {
        m_visible = false;
    }
    void show() {
        m_visible = true;
    }
    virtual void resize(unsigned int width, unsigned int height) {
        m_width = width;
        m_height = height;
    }
    virtual int type() = 0;
    void keyboardInputHandler(int ch);
private:
    unsigned int m_width = 0;
    unsigned int m_height = 1;
    bool m_visible = true;
};

#endif
