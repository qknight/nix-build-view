#include <curses.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "WindowManager.hpp"
#include "AdvancedString.hpp"
#include "TerminalWidget.hpp"



#define TIME_OUT 100

int main_loop = 1;

void keyboard_input_handler();
void check_logfile();
void check_JSON();

FILE* fp;
char * line = NULL;
size_t len = 0;
ssize_t read;



void keyboard_input_handler() {
    int ch;

    timeout(TIME_OUT);
    ch = getch(); /* Waits for TIME_OUT milliseconds */
    if (ch == ERR)
        return;
    /////////// BEGIN global shortcuts //////////////////////////
    if (ch == 'Q' || ch == 'q') {
        main_loop = 0;
        return;
    }
    /////////// END global shortcuts //////////////////////////

    // all other inputs are delegated to the windowmanager
    WindowManager::Instance()->keyboard_input_handler(ch);
}

void check_logfile() {
    //FIXME read as much as possible in one go and not line by line....
    ssize_t read;
    do {
        if ((read = getline(&line, &len, fp)) != -1) {
            AdvancedStringContainer s;
            s << line;
            TerminalWidget::Instance()->append(s);
        }
    } while (read > 0);
}

void check_JSON() {

}

int main(int argc, char *argv[]) {
    fp = fopen("logfile", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    initscr();	/* Start curses mode */
    start_color();
    cbreak(); /* Line buffering disabled. Pass on every thing */
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    noecho();
    WindowManager::Instance()->update();

    //FIXME think about pselect here...
    while (main_loop) {
        //FIXME not working right now
        check_logfile();
        check_JSON();
        keyboard_input_handler();
    }

    endwin(); /* End curses mode */

    //FIXME need a renderer for AdvancedString to shell *oh sigh*
//     std::cout << listWidget->log().str() << std::endl;

    return 0;
}



