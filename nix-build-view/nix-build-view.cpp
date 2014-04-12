#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

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

WindowManager* wm;
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
    if (ch == '1') {
        ;
    }
    if (ch == '2') {
        ;
    }
    if (ch == '3') {
        ;
    }
    if (ch == '4') {
        ;
    }
    if (ch == 'h' || ch == 'H') {
        ;//HELP
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
        wm->updateDimension();
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
// wm->addWidget(new BuildWidget("73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]"));
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

    wm = new WindowManager(stdscr);
    lw = new ListWidget();

    wm->addWidget(lw);
    wm->addWidget(new UrlWidget("1 http://url.com/nix/store/xay7d5hfhm9vjd3v31dbzimi08ydrgd4w-zlib-1.2.8", 0.4, 235));
    wm->addWidget(new UrlWidget("2 http://url.com/nix/store/bnasfgdddm9vj3v31dbdzimi08ydrgd4w-zlib-1.2.8", 1.0, 234045));
    wm->addWidget(new UrlWidget("3 http://url.com/nix/store/bnasfgdddm9vj3v31dbdzimi08ydrgd4w-zlib-1.2.8", 1.0, 234045));
    wm->addWidget(new UrlWidget("4 http://url.com/nix/store/bnasfgdddm9vj3v31dbdzimi08ydrgd4w-zlib-1.2.8", 1.0, 234045));
    wm->addWidget(new UrlWidget("5 http://url.com/nix/store/bnasfgdddm9vj3v31dbdzimi08ydrgd4w-zlib-1.2.8", 1.0, 234045));
    wm->addWidget(new UrlWidget("6 http://url.com/nix/store/asdy7d5hfhm9vj3v31dbzimi08ydrgd4w-zlib-1.2.8", 0.1, 33234045));
    wm->addWidget(new BuildWidget("1 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]"));
    wm->addWidget(new BuildWidget("2 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]"));
    wm->addWidget(new BuildWidget("3 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]"));
    wm->addWidget(new BuildWidget("4 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]"));
    wm->addWidget(new StatusWidget());

    // FIXME maybe this should be replaced by a pselect so rendering happens only on demand
    while (main_loop) {
        check_logfile(lw);
        check_JSON();
        check_usr_response();
        wm->render();
    }

    endwin(); /* End curses mode */

    //FIXME enable this once it starts making sense
//     std::cout << lw->log() << std::endl;
    
    //FIXME example code
    AdvancedStringList aout;
    aout << TermCtrl(MAGENTA) << "hello magenta world!" << TermCtrl(RESET) << "\n";
    std::cout << aout.color_str();

    return 0;
}


