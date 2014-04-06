#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

#define TIME_OUT 100

#define RESET       "\033[0m"
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



int main_loop = 1;
int test = 0;
std::stringstream log;

void check_usr_response();
void check_logfile();
void check_JSON();
void render_to_terminal(WINDOW *win);

int store_n_discs;

FILE* fp;
char * line = NULL;
size_t len = 0;
ssize_t read;

int main(int argc, char *argv[]) {
    fp = fopen("logfile", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    initscr();	/* Start curses mode */
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);
    cbreak(); /* Line buffering disabled. Pass on every thing */
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    noecho();

    // FIXME maybe this can be replaced by a pselect
    while (main_loop) {
        render_to_terminal(stdscr);
        check_logfile();
//         check_JSON();
        check_usr_response();
    }

    endwin(); /* End curses mode */
    std::cout << log.str() << std::endl;
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
        //FIXME call render_to_terminal(..)
    }
}

void check_logfile() {
    ssize_t read;
    do {
        if (read = getline(&line, &len, fp) != -1) {
            log << line;
        }
    } while (read > 0);
}

void check_JSON() {
}

void render_to_terminal(WINDOW *win) {
    wclear(win);
    attron(A_REVERSE);
//     mvprintw(0, 0, "F1 Help | q Exit", 1);
//     std::stringstream s;
//     s << "terminal resize event - LINES= " << LINES << ", COLS= " << COLS;

//     mvprintw(1, 0, s.str().c_str());
//
//     std::stringstream v;
//     v << "these text will hopefully be wrapped to show that ncurses will do this for us. there is a major problem with text using terminal escape sequences and ncurses, see this: " << MAGENTA << "should have color" << RESET;
//     mvprintw(0, 0, v.str().c_str());

//     mvprintw(0, 0, std::string("in theory here should be the log from stdin... but where is it?").c_str());
    mvprintw(0, 0, log.str().c_str());

    attron(COLOR_PAIR(2)); // for color support
    mvprintw(LINES-11, 0, std::string("|- building 9 targets:").c_str());
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(1)); // for color support
    mvprintw(LINES-10, 0, std::string(" |+ 3v30s57kyi85g7lb9irjv80s57kyi86-foobar-1.2.3 ......................... [1/8 fetchingPhase]").c_str());
    mvprintw(LINES-9, 0, std::string(" |+ 3v30s57kyi85g7lb9irjv80s57kyi86-foobar-1.2.3 ........................ [3/8 configurePhase]").c_str());
    mvprintw(LINES-8, 0, std::string(" |+ d3v357kyi85g7lb9firjv80s57fkyi8-foo-1.2.3 ............................... [5/8 buildPhase]").c_str());
    mvprintw(LINES-7, 0, std::string(" |+ 73v30s57kyi85g7lb9irjv80s57kyi1-psi-1.2.3 ........................ [8/8 installationPhase]").c_str());
    mvprintw(LINES-6, 0, std::string(" |+ ... 5 more (select to see) ...").c_str());
    attroff(COLOR_PAIR(1)); // for color support
    attron(COLOR_PAIR(3)); // for color support
    mvprintw(LINES-5, 0, std::string("|- fetching 3 targets").c_str());
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(1)); // for color support
    mvprintw(LINES-4, 0, std::string(" |+ http://cache.nixos.org/nar/0s57kyi85g7lb9irjv80s57kyi8-foobar-1.2.3.nar.xz . 10% 3.3 Mib/s").c_str());
    mvprintw(LINES-3, 0, std::string(" |+ http://cache.nixos.org/nar/kya2cslmh5vc23i4q35di8-foobar-1.2.3.nar.xz ...... 60% 2.3 Mib/s").c_str());
    mvprintw(LINES-2, 0, std::string(" |+ http://cache.nixos.org/nar/7kc3c3jc3yi8-foobar-1.2.3.nar.xz ................ 30% 1.3 Mib/s").c_str());
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(4));
    mvprintw(LINES-1, 0, std::string("nix-build | building: 4/9 | fetching: 3/3 | since 20m30s").c_str());
    attroff(COLOR_PAIR(4));
    attroff(A_REVERSE);
    test+=1;
    wrefresh(win);
}

