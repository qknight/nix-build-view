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

void check_usr_response();
void render_to_terminal(WINDOW *win);
char *status = "-\\|/";

int store_n_discs;

int main(int argc, char *argv[]) {
    initscr();	/* Start curses mode */
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    cbreak(); /* Line buffering disabled. Pass on every thing */
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

void render_to_terminal(WINDOW *win) {
    wclear(win);
    attron(A_REVERSE);
    mvprintw(0, 0, "Press F1 for help or q to Exit", 1);
    std::stringstream s;
    s << "terminal resize event - LINES= " << LINES << ", COLS= " << COLS;

    attron(COLOR_PAIR(1)); // for color support
    mvprintw(1, 0, s.str().c_str()); 
    attroff(COLOR_PAIR(1));
    mvwprintw(win, 2, 0, "%c", status[test%4]);
    
    for (int y = 0; y < LINES-6; ++y) {
        for(int i = 0; i < COLS; ++i) {
            if (i == COLS-1 || i == 0)
                mvwprintw(win, y+3, i, "%c", '|');
            else
                mvwprintw(win, y+3, i, "%i", i%10);
        }
    }

    std::stringstream v;
    v << "these derivations will be " << MAGENTA << "built" << RESET;
    mvprintw(LINES-3, 0, v.str().c_str());
//     mvprintw(LINES-3, 0, std::string("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world").c_str());

    mvprintw(LINES-1, 0, std::string("hello world").c_str());
    attroff(A_REVERSE);
    test+=1;
    wrefresh(win);
}

