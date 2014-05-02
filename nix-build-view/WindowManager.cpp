#include "WindowManager.hpp"
#include "Widget.hpp"
#include "AdvancedString.hpp"

#include <sys/ioctl.h>


WindowManager* WindowManager::Instance() {
    static WindowManager* _instance = new WindowManager(stdscr);
    return _instance;
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
    updateLayout();
}

// layout widgets on the canvas to later draw them
void WindowManager::updateLayout(int layout) {
    m_selectedLayout = layout;
    updateLayout();
}

// updates the layout, the structure which is drawn, based on the selected layout (m_selectedLayout)
void WindowManager::updateLayout() {
//   m_selectedLayout;
    if (m_widgets.size() > 0)
        m_widgets[0]->resize(width(), height()-m_widgets.size()+1);
    for(unsigned int i=0; i < m_widgets.size(); ++i) {
        Widget* w= m_widgets[i];
        w->resize(width(), w->height());
    }
}

void WindowManager::resize(int width, int height) {
    m_width = width;
    m_height = height;
    updateLayout();
    update();
}

//redraw individual widgets thus it has to know which widgets are visible
void WindowManager::update(Widget* w) {
    //FIXME need a layout to know what to do here...
}

// redraw the whole scene
void WindowManager::update() {
    //FIXME bug: when amount of lines written exceeds the number of visibile lines it removes a false amount of lines and damages the terminal output
    int pos=0;
    wclear(m_win);
    attron(A_REVERSE);
    AdvancedStringContainer as = m_widgets[0]->render();
    //FIXME add a function which checks the output to not exeed the boundingbox given!
    pos=0;
    for (unsigned int x=0; x < as.size(); ++x) {
        attron(as[x].attributes() | COLOR_PAIR(cm.setColor(COLOR_BLACK, as[x].fontColor())));
        mvprintw(x, 0, as[x].str().c_str());
        pos += as[x].str().size();
        attroff(as[x].attributes() | COLOR_PAIR(cm.setColor(COLOR_BLACK, as[x].fontColor())));
    }
    //FIXME this layout (compositing) is static and needs to be made dynamic -> need scenegraph
    for(unsigned int i=m_widgets.size()-1;  i >= 1 ; --i) {
        AdvancedStringContainer as = m_widgets[m_widgets.size()-i]->render();
        pos=0;
        for (unsigned int x=0; x < as.size(); ++x) {
            attron(as[x].attributes() | COLOR_PAIR(cm.setColor(as[x].bgColor(), as[x].fontColor())));
            mvprintw(height()-i, pos, as[x].str().c_str());
            pos+=as[x].str().size();
            attroff(as[x].attributes() | COLOR_PAIR(cm.setColor(as[x].bgColor(), as[x].fontColor())));
        }
    }
    wrefresh(m_win);
}


