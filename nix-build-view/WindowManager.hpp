#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class Widget;
class AdvancedString;
#include "ColorManager.hpp"

class WindowManager {
public:
    void update();
    void updateLayout(int type);
    void addWidget(Widget* w);
    void resize(int width, int height);
    int width() {
        return m_width;
    };
    int height() {
        return m_height;
    };
    static WindowManager* Instance();
    void update(Widget* w);
private:
    WindowManager(WINDOW *win);
    WINDOW* m_win;
    std::vector<Widget*> m_widgets;
    int m_width;
    int m_height;
    static WindowManager* m_pInstance;
    ColorManager cm;
};

#endif
