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

void check_JSON() {
    //FIXME read as much as possible in one go and not line by line....
//     ssize_t read;
//     do {
//         if ((read = getline(&line, &len, fp)) != -1) {
//             AdvancedStringContainer s;
//             s << line;
//             TerminalWidget::Instance()->append(s);
//         }
//     } while (read > 0);
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
    AdvancedStringContainer s;

    s << AdvancedString("nix-build-view ", COLOR_CYAN, WA_BOLD) << AdvancedString(WindowManager::Instance()->version(), COLOR_CYAN) << AdvancedString(" (c) 2014++ Joachim Schiele\n", COLOR_CYAN, WA_BOLD);
    s << AdvancedString("Released under the GNU GPL v3\n", COLOR_CYAN, WA_BOLD);
    s << AdvancedString("\n");
    s << AdvancedString("building Nix...\n");
    s << AdvancedString("these derivations will be ") << AdvancedString("built", COLOR_MAGENTA) << AdvancedString(":\n");
    s << AdvancedString("  /nix/store/4hh3935anmmhl13q8lmdkgdsxzh46gq6-") << AdvancedString("tig-1.1.drv\n", COLOR_MAGENTA);
    s << AdvancedString("  /nix/store/9brfbp9gk7x3qim52q49rckhw7vw08h2-") << AdvancedString("asciidoc-8.6.8.drv\n", COLOR_MAGENTA);
    s << AdvancedString("  /nix/store/ckn6dnnb0ayjbdn3avpqvqa5rs35k2w1-") << AdvancedString("tig-1.1.tar.gz.drv\n", COLOR_MAGENTA);
    s << AdvancedString("  /nix/store/j9bgfp4q6h8gdi4b6idvi1r39b5hagvz-") << AdvancedString("asciidoc-8.6.8.tar.gz.drv\n", COLOR_MAGENTA);
    s << AdvancedString("these paths will be ") << AdvancedString("fetched", COLOR_GREEN) << AdvancedString(" (") << AdvancedString("40.1", COLOR_YELLOW) << AdvancedString(" Mib download, ") << AdvancedString("201.66", COLOR_YELLOW) << AdvancedString(" Mib unpacked):\n");
    s << AdvancedString("  /nix/store/0yzz6p08k1sgpdb63c0wx48vx0yc51g6-") << AdvancedString("bzip2-1.0.6\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/1a08qk5q5vdfv13rwasbf4fqa2s26kx4-") << AdvancedString("attr-2.4.47\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/3amm865b2qb5s5mwvshvd9kpfq3aj1bc-") << AdvancedString("libssh2-1.4.3\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/5myfmphlck9gcabr6czlg6792d9zhh4m-") << AdvancedString("perl-DBI-1.630\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/j298bijkgdzzv6wlzdidldx297ch5rq2-") << AdvancedString("nix-1.7pre3327_0e2ca\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/mad928szz57gjpbfm9dih23hpspzz11f-") << AdvancedString("openssl-1.0.1f\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/q784x64hp3nwdxx7lbgb16f74i2bhxxk-") << AdvancedString("glibc-2.18\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/qw7vn33jcv1yfsfdw19ic5r2jlqk68w3-") << AdvancedString("bash-4.2-p45\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/skxdffb34mcz50f9q691qsg44bgrxg2x-") << AdvancedString("perl-DBD-SQLite-1.37\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/vmq6nmnvyblnwlrmhhhpnsjdlri4qz25-") << AdvancedString("curl-7.33.0\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xay7d5hfhm9vj3v31dbzimi08ydrgd4w-") << AdvancedString("zlib-1.2.8\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xkhr68z09y66c1qwzdq03lnhjl9c51si-") << AdvancedString("perl-WWW-Curl-4.15\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-") << AdvancedString("gzip-1.6\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/z1krxp2hwph8fypchf2b0ssnyp6z8k9l-") << AdvancedString("perl-5.16.3\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zp4bcz188h69jvrb1qyl10lfkanz7ld3-") << AdvancedString("boehm-gc-7.2d\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zsl05mbb69s38bbyi9nfff6vyry9m8jm-") << AdvancedString("gnutar-1.27.1\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zxvyl58mw530xf811nmm0i8b6nibwmw5-") << AdvancedString("coreutils-8.21\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/mad928szz57gjpbfm9dih23hpspzz11f-") << AdvancedString("openssl-1.0.1f\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/q784x64hp3nwdxx7lbgb16f74i2bhxxk-") << AdvancedString("glibc-2.18\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/qw7vn33jcv1yfsfdw19ic5r2jlqk68w3-") << AdvancedString("bash-4.2-p45\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/skxdffb34mcz50f9q691qsg44bgrxg2x-") << AdvancedString("perl-DBD-SQLite-1.37\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/vmq6nmnvyblnwlrmhhhpnsjdlri4qz25-") << AdvancedString("curl-7.33.0\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xay7d5hfhm9vj3v31dbzimi08ydrgd4w-") << AdvancedString("zlib-1.2.8\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xkhr68z09y66c1qwzdq03lnhjl9c51si-") << AdvancedString("perl-WWW-Curl-4.15\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-") << AdvancedString("gzip-1.6\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/z1krxp2hwph8fypchf2b0ssnyp6z8k9l-") << AdvancedString("perl-5.16.3\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zp4bcz188h69jvrb1qyl10lfkanz7ld3-") << AdvancedString("boehm-gc-7.2d\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zsl05mbb69s38bbyi9nfff6vyry9m8jm-") << AdvancedString("gnutar-1.27.1\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zxvyl58mw530xf811nmm0i8b6nibwmw5-") << AdvancedString("coreutils-8.21\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/mad928szz57gjpbfm9dih23hpspzz11f-") << AdvancedString("openssl-1.0.1f\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/q784x64hp3nwdxx7lbgb16f74i2bhxxk-") << AdvancedString("glibc-2.18\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/qw7vn33jcv1yfsfdw19ic5r2jlqk68w3-") << AdvancedString("bash-4.2-p45\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/skxdffb34mcz50f9q691qsg44bgrxg2x-") << AdvancedString("perl-DBD-SQLite-1.37\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/vmq6nmnvyblnwlrmhhhpnsjdlri4qz25-") << AdvancedString("curl-7.33.0\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xay7d5hfhm9vj3v31dbzimi08ydrgd4w-") << AdvancedString("zlib-1.2.8\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/xkhr68z09y66c1qwzdq03lnhjl9c51si-") << AdvancedString("perl-WWW-Curl-4.15\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-") << AdvancedString("gzip-1.6\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/z1krxp2hwph8fypchf2b0ssnyp6z8k9l-") << AdvancedString("perl-5.16.3\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zp4bcz188h69jvrb1qyl10lfkanz7ld3-") << AdvancedString("boehm-gc-7.2d\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zsl05mbb69s38bbyi9nfff6vyry9m8jm-") << AdvancedString("gnutar-1.27.1\n", COLOR_GREEN);
    s << AdvancedString("  /nix/store/zxvyl58mw530xf811nmm0i8b6nibwmw5-") << AdvancedString("coreutils-8.21\n", COLOR_GREEN);

    TerminalWidget::Instance()->append(s);

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

    while (main_loop) {
        check_JSON();
        keyboard_input_handler();
    }

    endwin(); /* End curses mode */

    //FIXME need a renderer for AdvancedString to shell *oh sigh*
    AdvancedStringContainer log =  TerminalWidget::Instance()->log();

    for(unsigned int i=0; i < log.size(); ++i)
        std::cout << log[i].terminalString();
    return 0;
}



