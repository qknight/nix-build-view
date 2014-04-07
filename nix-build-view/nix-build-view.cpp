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

int main(int argc, char *argv[]) {
    fp = fopen("logfile", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    initscr();	/* Start curses mode */
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_WHITE);
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
//     wm->addWidget(new UrlWidget("7 http://url.com/nix/store/asdy7d5hfhm9vj3v31dbzimi08ydrgd4w-zlib-1.2.8", 0.1, 33234045));

    // FIXME maybe this can be replaced by a pselect
    while (main_loop) {
        check_logfile(lw);
//         check_JSON();
        check_usr_response();
        wm->render(20,1);
    }

    endwin(); /* End curses mode */
//     std::cout << lw.str() << std::endl;
    return 0;
}

void check_usr_response() {
    int ch;

    //FIXME now the terminal is redrawn every TIME_OUT which is very often
    timeout(TIME_OUT);
    ch = getch(); /* Waits for TIME_OUT milliseconds */
    if (ch == ERR)
        return;
    if (ch == KEY_F(1))
        ;
    if (ch == 'Q' || ch == 'q') {
        main_loop = 0;
    }
    if (ch == KEY_F(2)) {

    }
    // this event indicates a SIG 28 SIGWINCH
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

}

// void render_to_terminal(WINDOW *win) {
//     wclear(win);
//     attron(A_REVERSE);
//     mvprintw(0, 0, log.str().c_str());
//
//     attron(COLOR_PAIR(2)); // for color support
//     mvprintw(LINES-11, 0, std::string("|- building 9 targets:").c_str());
//     attroff(COLOR_PAIR(2));
//     attron(COLOR_PAIR(1)); // for color support
//     mvprintw(LINES-10, 0, std::string(" |+ 3v30s57kyi85g7lb9irjv80s57kyi86-foobar-1.2.3 ......................... [1/8 fetchingPhase]").c_str());
//     mvprintw(LINES-9, 0, std::string(" |+ 3v30s57kyi85g7lb9irjv80s57kyi86-foobar-1.2.3 ........................ [3/8 configurePhase]").c_str());
//     mvprintw(LINES-8, 0, std::string(" |+ d3v357kyi85g7lb9firjv80s57fkyi8-foo-1.2.3 ............................... [5/8 buildPhase]").c_str());
//     mvprintw(LINES-7, 0, std::string(" |+ 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]").c_str());
//     mvprintw(LINES-6, 0, std::string(" |+ ... 5 more (select to see) ...").c_str());
//     attroff(COLOR_PAIR(1)); // for color support
//     attron(COLOR_PAIR(3)); // for color support
//     mvprintw(LINES-5, 0, std::string("|- fetching 3 targets").c_str());
//     attroff(COLOR_PAIR(3));
//     attron(COLOR_PAIR(1)); // for color support
//     mvprintw(LINES-4, 0, std::string(" |+ http://cache.nixos.org/nar/0s57kyi85g7lb9irjv80s57kyi8-foobar-1.2.3.nar.xz . 10% 3.3 Mib/s").c_str());
//     mvprintw(LINES-3, 0, std::string(" |+ http://cache.nixos.org/nar/kya2cslmh5vc23i4q35di8-foobar-1.2.3.nar.xz ...... 60% 2.3 Mib/s").c_str());
//     mvprintw(LINES-2, 0, std::string(" |+ http://cache.nixos.org/nar/7kc3c3jc3yi8-foobar-1.2.3.nar.xz ................ 30% 1.3 Mib/s").c_str());
//     attroff(COLOR_PAIR(1));
//     attron(COLOR_PAIR(4));
//     mvprintw(LINES-1, 0, std::string("nix-build | building: 4/9 | fetching: 3/3 | since 20m30s").c_str());
//     attroff(COLOR_PAIR(4));
//     attroff(A_REVERSE);
//     test+=1;
//     wrefresh(win);
// }

