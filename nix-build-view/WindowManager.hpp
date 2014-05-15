#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <curses.h>

#include "ColorManager.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class Widget;
class Layout;
class AdvancedString;
class TerminalWidget;
class StatusWidget;
class HelpWidget;
class VerticalSpacerWidget;


class WindowManager {
public:
    void update(Widget* w = NULL);
    void setLayout(int layout);
    void addLayout(Layout* l);
    void resize(int width, int height);
    int width() {
        return m_width;
    };
    int height() {
        return m_height;
    };
    static WindowManager* Instance();
    void keyboardInputHandler(int ch);
private:
    WindowManager(WINDOW *win);
    void setKeyboardInputHandler(Widget* w);
    WINDOW* m_win;
    int m_width;
    int m_height;
    ColorManager cm;
    unsigned int m_selectedLayout=0;

    StatusWidget* statusWidget;
    HelpWidget* helpWidget;
    VerticalSpacerWidget* verticalSpacer;
    
    std::vector<Layout*> m_layouts;
    Widget* m_focusWidget = NULL;

};

#endif
