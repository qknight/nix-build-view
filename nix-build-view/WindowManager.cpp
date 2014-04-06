#include "WindowManager.hpp"
#include "Widget.hpp"

#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif


WindowManager::WindowManager(WINDOW* win) {
    m_win = win;
    updateDimension();
}

void WindowManager::render(int w, int h) {
    wclear(m_win);
    attron(A_REVERSE);
    int n = m_widgets.size()-1;
    mvprintw(0, 0, m_widgets[0]->render(width(),height()-n).c_str());
    for(int i=m_widgets.size()-1;  i >= 1 ; --i) {
        mvprintw(height()-i, 0, m_widgets[m_widgets.size()-i]->render(width(),1).c_str());
    }
    wrefresh(m_win);
}

void WindowManager::addWidget(Widget* w) {
    m_widgets.push_back(w);
}

void WindowManager::updateDimension() {
    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
    m_width = size.ws_col;
    m_height = size.ws_row;
    //printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
}
