#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class Widget;

class WindowManager {
public:
    WindowManager(WINDOW *win);
    void render(int w, int h);
    void addWidget(Widget* w);
    void updateDimension();
    int width() { return m_width; };
    int height() { return m_height; };
private:
    WINDOW* m_win;
    std::vector<Widget*> m_widgets;
    int m_width;
    int m_height;
};

#endif
