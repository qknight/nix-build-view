#include "WindowManager.hpp"
#include "Widget.hpp"
#include "Layout.hpp"
#include "AdvancedString.hpp"

#include "UrlWidget.hpp"
#include "TerminalWidget.hpp"
#include "BuildWidget.hpp"
#include "StatusWidget.hpp"
#include "HelpWidget.hpp"
#include "VerticalSpacerWidget.hpp"

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


    statusWidget = new StatusWidget();
    verticalSpacer = new VerticalSpacerWidget();
    Layout* l1 = new Layout;

    helpWidget = new HelpWidget();
    l1->addWidget(helpWidget);
    l1->addWidget(verticalSpacer);
    l1->addWidget(statusWidget);

    Layout* l2 = new Layout;

    TerminalWidget* terminalWidget = TerminalWidget::Instance();
    l2->addWidget(terminalWidget);
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    l2->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    UrlWidget* uw = new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.1, 33234045);
    l2->addWidget(uw);
    l2->addWidget(new BuildWidget("/nix/store/wr14w82r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    l2->addWidget(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    l2->addWidget(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    l2->addWidget(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    BuildWidget* bw =  new BuildWidget("/nix/store/y3rjpblyrjs3xdhvkdgfw327m7594ann-nixos-14.04pre42009.3f1af5f", "barPhase 1/8");
    l2->addWidget(bw);
    l2->addWidget(statusWidget);

    Layout* l3 = new Layout;
    l3->addWidget(terminalWidget);
    l3->addWidget(statusWidget);

    Layout* l4 = new Layout;
    l4->addWidget(verticalSpacer);
    l4->addWidget(uw);
    l4->addWidget(statusWidget);

    Layout* l5 = new Layout;
    l5->addWidget(verticalSpacer);
    l5->addWidget(bw);
    l5->addWidget(statusWidget);

    addLayout(l1);
    addLayout(l2);
    addLayout(l3);
    addLayout(l4);
    addLayout(l5);

    setLayout(1);
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

void WindowManager::keyboard_input_handler(int ch) {
//      0 - help widget
    //      1 - composed view: input should be forwarded to the log
    //      2 - like 1 but log has fullscreen
    //      3 - fetch is fullscreen and is scrollable
    //      4 - build is fullscreen and is scrollable
    if (ch == '1' || ch == '2' || ch == '3' || ch == '4') {
        setLayout(ch-48);
        statusWidget->setFocus(ch-48);
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
    if (ch == KEY_HOME || ch == KEY_END || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_PPAGE || ch == KEY_NPAGE) {
        TerminalWidget::Instance()->keyboardInputHandler(ch);
        return;
    }
    //FIXME, all unhandled events should be directed to the focus widget
}

