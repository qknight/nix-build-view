#include "WindowManager.hpp"
#include "Widget.hpp"
#include "Layout.hpp"
#include "AdvancedString.hpp"

#include "FetchWidget.hpp"
#include "TerminalWidget.hpp"
#include "BuildWidget.hpp"
#include "StatusWidget.hpp"
#include "HelpWidget.hpp"
#include "VerticalSpacerWidget.hpp"
#include "FetchWidgetManager.hpp"
#include "BuildWidgetManager.hpp"

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

    statusWidget = StatusWidget::Instance();
    verticalSpacer = new VerticalSpacerWidget();
    Layout* l1 = new Layout;

    helpWidget = new HelpWidget();
    l1->addWidget(helpWidget);
    l1->addWidget(verticalSpacer, 0);
    l1->addWidget(statusWidget);

    Layout* l2 = new Layout;

    TerminalWidget* terminalWidget = TerminalWidget::Instance();
    l2->addWidget(terminalWidget);

    BuildWidgetManager* buildWidgetManager = BuildWidgetManager::Instance();
    FetchWidgetManager* fetchWidgetManager = FetchWidgetManager::Instance();

    l2->addWidget(buildWidgetManager, 4);
    l2->addWidget(fetchWidgetManager, 4);

    l2->addWidget(statusWidget);

    Layout* l3 = new Layout;
    l3->addWidget(terminalWidget);
    l3->addWidget(statusWidget);

    Layout* l4 = new Layout;
    l4->addWidget(verticalSpacer,0);
    l4->addWidget(fetchWidgetManager,4000);
    l4->addWidget(statusWidget);

    Layout* l5 = new Layout;
    l5->addWidget(verticalSpacer,0);
    l5->addWidget(buildWidgetManager,4000);
    l5->addWidget(statusWidget);

    addLayout(l1);
    addLayout(l2);
    addLayout(l3);
    addLayout(l4);
    addLayout(l5);

    setLayout(1);
    setKeyboardInputHandler(TerminalWidget::Instance());
}

void WindowManager::addLayout(Layout* l) {
    m_layouts.push_back(l);
}

// layout widgets on the canvas to later draw them
void WindowManager::setLayout(int layout) {
    m_selectedLayout = layout;
}

void WindowManager::resize(int width, int height) {
    m_width = width;
    m_height = height;
    update();
}

// redraw the whole screen
void WindowManager::update(Widget* w) {
    //FIXME do not clear and redraw the whole screen
    wclear(m_win);
    if (w == NULL)
        ; //FIXME redraw everything
    else
        ;//FIXME redraw only single widget space

    //FIXME bug: when amount of lines written exceeds the number of visibile lines it removes a false amount of lines and damages the terminal output
    int pos=0;
    int heightpointer = 0;
    attron(A_REVERSE);
    if (m_selectedLayout > m_layouts.size())
        return;
    Layout* l = m_layouts[m_selectedLayout];

    // layout the widget in the current terminal width/height
    //FIXME add check if width and height is not exceeded
    RasterizedLayout r = l->rasterize(width(), height());

    for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
        FixedWidget fw = r.m_fixedWidgets[i];
        AdvancedStringContainer as = fw.widget->render(fw.width, fw.height);
        pos=0;
        for (unsigned int x=0; x < as.size(); ++x) {
            attron(as[x].attributes() | COLOR_PAIR(cm.setColor(as[x].bgColor(), as[x].fontColor())));
            mvprintw(heightpointer+(pos/width()), pos%width(), as[x].str().c_str());
            pos+=as[x].str().size();
            attroff(as[x].attributes() | COLOR_PAIR(cm.setColor(as[x].bgColor(), as[x].fontColor())));
        }
        heightpointer += fw.height;
    }
    wrefresh(m_win);//FIXME do i need this?
}

void WindowManager::keyboardInputHandler(int ch) {
//      0 - help widget
    //      1 - composed view: input should be forwarded to the log
    //      2 - like 1 but log has fullscreen
    //      3 - fetch is fullscreen and is scrollable
    //      4 - build is fullscreen and is scrollable
    if (ch == '1' || ch == '2' || ch == '3' || ch == '4') {
        int w = ch-48;
        setLayout(w);
        statusWidget->setFocus(w);
        switch(w) {
        case 1:
        case 2:
            setKeyboardInputHandler(TerminalWidget::Instance());
            break;
        case 3:
            setKeyboardInputHandler(FetchWidgetManager::Instance());
            break;
        case 4:
            setKeyboardInputHandler(BuildWidgetManager::Instance());
            break;
        default:
            setKeyboardInputHandler(NULL);
        };
        return;
    }
    if (ch == 'h' || ch == 'H') {
        setLayout(0);
        statusWidget->setFocus(0);
        return;
    }
    //FIXME for testing only
    if (ch == 't' || ch == 'T') {
        AdvancedStringContainer s;

        s << AdvancedString("**this should be colored in MAGENTA**\n", COLOR_MAGENTA);
        s << AdvancedString("**this should be colored in GREEN**\n", COLOR_GREEN);
        s << AdvancedString("----------------------1111111111111111111111111122222222222222222222222222222222233333333333333333333333333333333334444444\n", COLOR_GREEN);
        s << AdvancedString("\n\na\n");
	s << "Version: " << AdvancedString(version());
        TerminalWidget::Instance()->append(s);
        return;
    }
    // this event indicates a SIG 28 - SIGWINCH
    if (ch == KEY_RESIZE) {
        struct winsize size;
        if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
            printf("TIOCGWINSZ error");
        resize(size.ws_col, size.ws_row);
        return;
    }
    if (m_focusWidget)
        m_focusWidget->keyboardInputHandler(ch);
}

void WindowManager::setKeyboardInputHandler(Widget* w) {
    m_focusWidget = w;
}

std::string WindowManager::version() {
    return std::string(VERSION);
}
