#ifndef WIDGET__HPP
#define WIDGET__HPP

#include "WindowManager.hpp"
#include "AdvancedString.hpp"

namespace WidgetName {
enum {
    HelpWidget,
    TerminalWidget,
    FetchWidget,
    BuildWidget,
    StatusWidget,
    VerticalSpacerWidget,
    FetchWidgetManager,
    BuildWidgetManager,
};
};

class Widget {
public:
    virtual AdvancedStringContainer render(unsigned int width, unsigned int height) = 0;
    void update() {
        WindowManager::Instance()->update(this);
    }

//     void hide() {
//         m_visible = false;
//     }
//     void show() {
//         m_visible = true;
//     }
    virtual int type() = 0;
    void keyboardInputHandler(int ch);
    virtual unsigned int rowsNeeded() {
      return 1;
    }

private:
    bool m_visible = true;
};

#endif
