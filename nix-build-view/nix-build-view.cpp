#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "ColorCodes.h"
#include "WindowManager.hpp"
#include "UrlWidget.hpp"
#include "ListWidget.hpp"
#include "BuildWidget.hpp"
#include "StatusWidget.hpp"
#include "AdvancedString.hpp"

#define TIME_OUT 100

int main_loop = 1;

void check_usr_response();
void check_logfile(ListWidget* lw);
void check_JSON();

FILE* fp;
char * line = NULL;
size_t len = 0;
ssize_t read;

ListWidget* lw;

void check_usr_response() {
    int ch;

    //FIXME now the terminal is redrawn every TIME_OUT which is very often
    timeout(TIME_OUT);
    ch = getch(); /* Waits for TIME_OUT milliseconds */
    if (ch == ERR)
        return;
    if (ch == 'Q' || ch == 'q') {
        main_loop = 0;
    }
    if (ch == KEY_LEFT)
        ;
    if (ch == KEY_RIGHT)
        ;
    //FIXME redirect none-global shortcuts to the respective widgets like
    //      - 1 - composed view: input should be forwarded to the log
    //      - 2 - like 1 but log has fullscreen
    //      - 3 - fetch is fullscreen and is scrollable
    //      - 4 - build is fullscreen and is scrollable
    if (ch == '1') {
        WindowManager::Instance()->updateLayout(1);
    }
    if (ch == '2') {
        WindowManager::Instance()->updateLayout(1);
    }
    if (ch == '3') {
        WindowManager::Instance()->updateLayout(1);
    }
    if (ch == '4') {
        WindowManager::Instance()->updateLayout(1);
    }
    if (ch == 'h' || ch == 'H') {
        WindowManager::Instance()->updateLayout(0);
    }
    //FIXME left/right, up/down, pgup/pwdn, home/end for ListWidget
    if (ch == KEY_HOME)
        lw->home();
    if (ch == KEY_END)
        lw->end();
    if (ch == KEY_UP)
        lw->up();
    if (ch == KEY_DOWN)
        lw->down();
    if (ch == KEY_PPAGE)
        lw->pgup();
    if (ch == KEY_NPAGE)
        lw->pgdown();


    // this event indicates a SIG 28 - SIGWINCH
    if (ch == KEY_RESIZE) {
        struct winsize size;
        if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
            printf("TIOCGWINSZ error");
        WindowManager::Instance()->resize(size.ws_col, size.ws_row);
    }
}

void check_logfile(ListWidget* lw) {
    ssize_t read;
    do {
        if (read = getline(&line, &len, fp) != -1) {
            lw->append(line);
        }
    } while (read > 0);
}

void check_JSON() {
// WindowManager::Instance()->addWidget(new BuildWidget(" [8/8 installationPhase]"));
}


int main(int argc, char *argv[]) {
    fp = fopen("logfile", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    initscr();	/* Start curses mode */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(3, COLOR_MAGENTA, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    cbreak(); /* Line buffering disabled. Pass on every thing */
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    noecho();

    lw = new ListWidget();
    WindowManager::Instance()->addWidget(lw);

    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
//     WindowManager::Instance()->addWidget(new UrlWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    WindowManager::Instance()->addWidget(new BuildWidget("/nix/store/wr14w82r2faqdmxq0k9f959lbz92mq41-etc [8/8 installationPhase]"));
    WindowManager::Instance()->addWidget(new BuildWidget("/nix/store/y3rjpblyrjs3xdhvkdgfw327m7594ann-nixos-14.04pre42009.3f1af5f [8/8 installationPhase]"));
    WindowManager::Instance()->addWidget(new BuildWidget("/nix/store/y3rjpblyrjs3xdhvkdgfw327m7594ann-nixos-14.04pre42009.3f1af5f [8/8 installationPhase]"));
    WindowManager::Instance()->addWidget(new StatusWidget());

    WindowManager::Instance()->update();
    
    while (main_loop) {
        check_logfile(lw);
        check_JSON();
        check_usr_response();
    }

    endwin(); /* End curses mode */

    //FIXME enable this once it starts making sense
//     std::cout << lw->log() << std::endl;

//     FIXME example code
    AdvancedStringList aout;
    aout << TermCtrl(MAGENTA) << "hello magenta world!" << TermCtrl(RESET) << "\n";
    std::cout << aout.color_str();

    return 0;
}



