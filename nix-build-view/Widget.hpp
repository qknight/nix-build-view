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
    virtual void keyboardInputHandler(int ch) {};
    // interesting for nested widget rendering
    virtual unsigned int rowsWantedByWidget() {
      return 1;
    }

private:
    bool m_visible = true;
};

#endif
