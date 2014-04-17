#include "WindowManager.hpp"
#include "Widget.hpp"
#include "AdvancedString.hpp"
#include <sys/ioctl.h>

WindowManager* WindowManager::m_pInstance = NULL;

WindowManager* WindowManager::Instance() {
    if(!m_pInstance)
        m_pInstance = new WindowManager(stdscr);

    return m_pInstance;
}

WindowManager::WindowManager(WINDOW* win) {
    m_win = win;

    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
    m_width = size.ws_col;
    m_height = size.ws_row;
}

void WindowManager::addWidget(Widget* w) {
    m_widgets.push_back(w);
    w->resize(width(), w->height());
    updateLayout(1);
}

// layout widgets on the canvas to later draw them
void WindowManager::updateLayout(int type) {
    if (m_widgets.size() > 0)
        m_widgets[0]->resize(width(), height()-m_widgets.size()+1);
    for(int i=0; i < m_widgets.size(); ++i) {
        Widget* w= m_widgets[i];
        w->resize(width(), w->height());
    }
}

void WindowManager::resize(int width, int height) {
    m_width = width;
    m_height = height;
    updateLayout(1);
    update();
}

//redraw individual widgets thus it has to know which widgets are visible
void WindowManager::update(Widget* w) {
  //FIXME need a scene-graph!
}

// redraw the whole scene
void WindowManager::update() {
    //FIXME bug: when amount of lines written exceeds the number of visibile lines it removes a false amount of lines and damages the terminal output
    wclear(m_win);
    attron(A_REVERSE);
    int n = m_widgets.size()-1;
    attron(COLOR_PAIR(1)); // for color support
    //FIXME add a function which checks the output to not exeed the boundingbox given!
    mvprintw(0, 0, m_widgets[0]->render().c_str());
    attroff(COLOR_PAIR(1)); // for color support

    //FIXME this layout (compositing) is static and needs to be made dynamic -> need scenegraph
    for(int i=m_widgets.size()-1;  i >= 1 ; --i) {
        attron(COLOR_PAIR(2)); // for color support
        mvprintw(height()-i, 0, m_widgets[m_widgets.size()-i]->render().c_str());
        attroff(COLOR_PAIR(2)); // for color support
    }
    wrefresh(m_win);
}



