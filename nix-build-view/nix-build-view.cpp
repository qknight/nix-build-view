#include <curses.h>
#include <string>

#include "WindowManager.hpp"
#include "AdvancedString.hpp"
#include "TerminalWidget.hpp"
#include "ColorCodes.h"
#include "TDD-nix-build.hpp"

#define TIME_OUT 1000

void
keyboard_input_handler()
{
    int ch;
    timeout(TIME_OUT);
    ch = getch(); /* Waits for TIME_OUT milliseconds */

    if (ch == ERR) {
        return;
    }

    // all other inputs are delegated to the windowmanager
    WindowManager::Instance()->keyboardInputHandler(ch);
}

int
main(int argc, char *argv[])
{
    initscr();	/* Start curses mode */
    start_color();
    cbreak(); /* Line buffering disabled. Pass on every thing */
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    noecho();

    WindowManager::Instance()->update();

    AdvancedStringContainer s;
    s << AdvancedString("nix-build-view ", COLOR_CYAN, WA_BOLD)
      << AdvancedString(WindowManager::Instance()->version(), COLOR_CYAN)
      << AdvancedString(" (c) 2014++ Joachim Schiele\n", COLOR_CYAN, WA_BOLD);
    s << AdvancedString("Released under the GNU GPL v3\n", COLOR_CYAN, WA_BOLD);
    s << AdvancedString("\n");

    TerminalWidget::Instance()->append(s);

    NixBuild* nixBuild = new NixBuild();

    while (WindowManager::Instance()->EventLoop()) {
        nixBuild->tick(); // simulates nix-build events
        keyboard_input_handler();
    }

    endwin(); /* End curses mode */

    AdvancedStringContainer log =  TerminalWidget::Instance()->log();
    for (unsigned int i = 0; i < log.size(); ++i) {
        std::cout << log[i].terminalString();
    }

    return 0;
}

