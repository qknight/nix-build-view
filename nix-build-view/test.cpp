#include <curses.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <sstream>

#define POSX 10
#define POSY 5
#define DISC_CHAR '*'
#define PEG_CHAR '#'
#define TIME_OUT 100

int main_loop = 1;
int test = 0;

void check_usr_response();
void render_to_terminal(WINDOW *win);
char *status = "-\\|/";

int store_n_discs;

int main(int argc, char *argv[]) {
    initscr();	/* Start curses mode 		*/
    cbreak();	/* Line buffering disabled. Pass on every thing */
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    noecho();

    // maybe this can be replaced by a pselect
    while (main_loop) {
        render_to_terminal(stdscr);
        check_usr_response();
    }

    endwin(); /* End curses mode */
    return 0;
}

void check_usr_response() {
    int ch;

    timeout(TIME_OUT);
    ch = getch(); /* Waits for TIME_OUT milliseconds */
    if (ch == ERR)
        return;
    if (ch == KEY_F(1) || ch == 'Q' || ch == 'q') {
        main_loop = 0;
    }
    if (ch == KEY_F(2)) {
    }
    // this event indicates a SIG 28 SIGWINCH
    if (ch == KEY_RESIZE) {
        //FIXME call render_to_terminal(..)
    }
}

void render_to_terminal(WINDOW *win) {
    wclear(win);
    attron(A_REVERSE);
    mvprintw(0, 0, "Press F1 or q to Exit");
    std::stringstream s;
    s << "terminal resize event - LINES= " << LINES << ", COLS= " << COLS;
    mvprintw(1, 0, s.str().c_str());
    mvwprintw(win, 2, 0, "%c", status[test%4]);
    for (int y = 0; y < LINES-4; ++y) {
        for(int i = 0; i < COLS; ++i) {
            if (i == COLS-1 || i == 0)
                mvwprintw(win, y+3, i, "%c", '|');
            else
                mvwprintw(win, y+3, i, "%i", i%10);
        }
    }
    mvprintw(LINES-1, 0, std::string("hello world").c_str());
    attroff(A_REVERSE);
    test+=1;
    wrefresh(win);
}

