#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <curses.h>

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
#include "ColorManager.hpp"

class WindowManager {
public:
    void update();
    void setLayout(int layout);
//     void updateLayout();
    void addLayout(Layout* l);
    void resize(int width, int height);
    int width() {
        return m_width;
    };
    int height() {
        return m_height;
    };
    static WindowManager* Instance();
    void update(Widget* w);
    void keyboard_input_handler(int ch);
private:
    WindowManager(WINDOW *win);
    WINDOW* m_win;
    int m_width;
    int m_height;
    ColorManager cm;
    int m_selectedLayout=0;

    TerminalWidget* terminalWidget;
    StatusWidget* statusWidget;
    HelpWidget* helpWidget;
    
    std::vector<Layout*> m_layouts;

};

#endif
