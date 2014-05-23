#include <curses.h>

#include <string>
#include <iostream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "WindowManager.hpp"
#include "AdvancedString.hpp"
#include "TerminalWidget.hpp"
#include "FetchWidgetManager.hpp"
#include "BuildWidgetManager.hpp"
#include "ColorCodes.h"

#include "FetchWidget.hpp"
#include "BuildWidget.hpp"

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
    WindowManager::Instance()->keyboardInputHandler(ch);
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

    BuildWidgetManager* buildWidgetManager = BuildWidgetManager::Instance();
    FetchWidgetManager* fetchWidgetManager = FetchWidgetManager::Instance();

    fetchWidgetManager->add(new FetchWidget("1http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("2http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("3http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("4http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("5http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("6http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("7http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("8http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("9http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("10http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("11http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("12http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("13http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("14http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("15http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("16http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("17http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("18http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("19http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("20http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("21http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("22http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("23http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("24http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("25http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("26http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("27http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("28http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.4, 235));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/07paqfjj437c0mhnkrbli70wlb5liqrnjcid81v66qlmy38r7ygx.nar.xz", 0.08, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 1.0, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/23v55vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz", 0.9, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/0s5v8pi4gh19k0jc7nf3.nar.xz", 0.5, 234045));
    fetchWidgetManager->add(new FetchWidget("http://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.01, 33234045));
    fetchWidgetManager->add(new FetchWidget("lasthttp://cache.nixos.org/nar/8pi4gh19k0jc7nf3.nar.xz", 0.05, 33234045));

    buildWidgetManager->add(new BuildWidget("1/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("2/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("3/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("4/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("5/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("6/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("7/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("8/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("9/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("10/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("11/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("12/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("13/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("14/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("15/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("16/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("17/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("18/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("19/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("20/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("21/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("22/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("23/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("24/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("25/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("26/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("27/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("28/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("29/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/wr14w8ksvfqr6992r2faqdmxq0k9f959lbz92mq41-etc", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj518yi8cqdksvfqr6991j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zgyxksvfqr699bc2a0bj5ksvfqr69918yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));
    buildWidgetManager->add(new BuildWidget("/nix/store/z9xdx4kdhq0yy0vh8lf7ngpbcxvap03a-parley-4.11.5", "buildPhase 4/7"));
    buildWidgetManager->add(new BuildWidget("/nix/store/zbbmg0dd4yjb1n60iyk9bakw2l9f4ikl-filelight-4.11.5", "fooPhase 1/8"));
    buildWidgetManager->add(new BuildWidget("last/nix/store/zgyxksvfqr69ksvfqr6999bc2a0bj518yi8cqd1j0-libkdcraw-4.11.5", "installationPhase 5/8"));

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



