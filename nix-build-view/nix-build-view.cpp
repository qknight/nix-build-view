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
#include "FetchWidgetManager.hpp"
#include "BuildWidgetManager.hpp"
#include "ColorCodes.h"

#include "FetchWidget.hpp"
#include "BuildWidget.hpp"

#define TIME_OUT 100

int main_loop = 1;

#define UNITTEST

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

#ifdef UNITTEST
void test1(AdvancedStringContainer& a, std::vector<AdvancedStringContainer> res, int num) {
    std::vector<AdvancedStringContainer> t;
    AdvancedStringContainer::containerStringSplit(t, a, '\n');

    bool r = true;

    if (t.size() != res.size() )
        r=false;

    if (r) {
        for (int i=0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r=false;
                break;
            }
        }
    }
    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST containerStringSplit----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "result was:" << std::endl;
        for (int i=0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }
        std::cout <<   "but should be:" <<  std::endl;
        for (int i=0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }
        std::cout << YELLOW << "---------------------------END TEST containerStringSplit----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}




void test2(AdvancedStringContainer& a, std::vector<AdvancedStringContainer> res, int num) {
    std::vector<AdvancedStringContainer> t;
    AdvancedStringContainer::trimTrailingNewlines(t, a);

    bool r = true;

    if (t.size() != res.size() )
        r=false;

    if (r) {
        for (int i=0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r=false;
                break;
            }
        }
    }
    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST trimTrailingNewlines----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "==== input was: ====" << std::endl;
        for (int i=0; i < a.size(); ++i) {
            std::cout  << "'" << YELLOW << a[i].str() << RESET << "'" << std::endl;
        }
        std::cout << "==== result was: ====" << std::endl;
        for (int i=0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }
        std::cout <<   "==== but should be: ====" <<  std::endl;
        for (int i=0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }
        std::cout << YELLOW << "---------------------------END TEST trimTrailingNewlines----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

void test3(AdvancedStringContainer& a, std::vector<AdvancedStringContainer> res, int width, int num) {
    std::vector<AdvancedStringContainer> t;

    AdvancedStringContainer::terminal_rasterize(t, a, width);

    bool r = true;

    if (t.size() != res.size() )
        r=false;

    if (r) {
        for (int i=0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r=false;
                break;
            }
        }
    }
    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST terminal_rasterize----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "==== input was: ====" << std::endl;
        for (int i=0; i < a.size(); ++i) {
            std::cout  << "'" << YELLOW << a[i].str() << RESET << "'" << std::endl;
        }
        std::cout << "==== result was: ====" << std::endl;
        for (int i=0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }
        std::cout <<   "==== but should be: ====" <<  std::endl;
        for (int i=0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }
        std::cout << YELLOW << "---------------------------END TEST terminal_rasterize----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}
#endif

int main(int argc, char *argv[]) {


#ifdef UNITTEST
    {
        AdvancedStringContainer a;
        a << AdvancedString("");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        res.push_back(e);
        test1(a, res, 1);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString(" what");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString(" what");
        res.push_back(e);
        test1(a, res, 2);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("foo \n");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e, e2;
        e << AdvancedString("foo ");
        res.push_back(e);
        e << AdvancedString("");
        res.push_back(e2);
        test1(a, res, 3);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\n1\n\n1\n1\n1\n1\n");
        a << AdvancedString("\n\n1\n\n\n\n1");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        AdvancedStringContainer e1;
        e1 << AdvancedString("1");
        res.push_back(e);
        res.push_back(e1);
        res.push_back(e);

        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e);
        res.push_back(e);

        res.push_back(e1);
        res.push_back(e);
        res.push_back(e);
        res.push_back(e);
        res.push_back(e1);
        test1(a, res, 4);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\n1\n\n1\n1\n1\n1\n\n\n1\n\n\n\n1");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        AdvancedStringContainer e1;
        e1 << AdvancedString("1");
        res.push_back(e);
        res.push_back(e1);
        res.push_back(e);

        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e1);
        res.push_back(e);
        res.push_back(e);

        res.push_back(e1);
        res.push_back(e);
        res.push_back(e);
        res.push_back(e);
        res.push_back(e1);
        test1(a, res, 5);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("hello\nworld");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("hello");
        AdvancedStringContainer e1;
        e1 << AdvancedString("world");
        res.push_back(e);
        res.push_back(e1);
        test1(a, res, 6);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\nhelloworld");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        AdvancedStringContainer e1;
        e1 << AdvancedString("helloworld");
        res.push_back(e);
        res.push_back(e1);
        test1(a, res, 7);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\n11akf__\n__jaffka22") << AdvancedString("33akfkafk44\n55asdkfasdfk66") << AdvancedString("\n77afafaf88\n\n\nf");
        std::vector<AdvancedStringContainer> res;

        AdvancedStringContainer e,e1,e2,e3,e4,e5,e6,e7;
        e << AdvancedString("");
        res.push_back(e);

        e1 << AdvancedString("11akf__");
        res.push_back(e1);
        e2 << AdvancedString("__jaffka2233akfkafk44");
        res.push_back(e2);
        e3 << AdvancedString("55asdkfasdfk66");
        res.push_back(e3);
        e4 << AdvancedString("77afafaf88");
        res.push_back(e4);
        e5 << AdvancedString("");
        res.push_back(e5);
        e6 << AdvancedString("");
        res.push_back(e6);
        e7 << AdvancedString("f");
        res.push_back(e7);

        test1(a, res,8);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\n");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e, e2;
        e << AdvancedString("");
        res.push_back(e);
        e << AdvancedString("");
        res.push_back(e2);
        test1(a, res, 9);
    }
    {
        AdvancedStringContainer a;
        a << AdvancedString("\n");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        res.push_back(e);
        res.push_back(e);
        test1(a, res, 10);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("linux                          ");
        b << AdvancedString("for  \n      the  ");
        b << AdvancedString("ppl    ");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e1;
        e << AdvancedString("linux                          for");
        e1 << AdvancedString("      the  ppl");
        res.push_back(e);
        res.push_back(e1);
        test2(b, res, 50);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        res.push_back(e);
        test2(b, res, 51);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("  ");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        res.push_back(e);
        test2(b, res, 52);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("  ");
        b << AdvancedString("");
        b << AdvancedString("");
        b << AdvancedString("  ");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e;
        e << AdvancedString("");
        res.push_back(e);
        res.push_back(e);
        res.push_back(e);
        res.push_back(e);
        test2(b, res, 53);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("  ");
        b << AdvancedString(" \n ");
        b << AdvancedString("  foo\n");
        b << AdvancedString(" bar  ");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e1,e2,e3;
        e << AdvancedString("");
        res.push_back(e);
        e << AdvancedString("");
        res.push_back(e);
        e1 << AdvancedString("   foo");
        res.push_back(e1);
        e2 << AdvancedString(" bar");
        res.push_back(e2);
        test2(b, res, 54);
    }
    {
        AdvancedStringContainer b;
        b << AdvancedString("**this should be colored in MAGENTA**\n", COLOR_MAGENTA);
        b << AdvancedString("**this should be colored in GREEN**\n", COLOR_GREEN);
        b << AdvancedString("----------------------1111111111111111111111111122222222222222222222222222222222233333333333333333333333333333333334444444\n", COLOR_GREEN);
        b << AdvancedString("\n\na");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e1,e2,e3,e4;
        e << AdvancedString("**this should be colored in MAGENTA**");
        res.push_back(e);
        e1 << AdvancedString("**this should be colored in GREEN**");
        res.push_back(e1);
        e2 << AdvancedString("----------------------1111111111111111111111111122222222222222222222222222222222233333333333333333333333333333333334444444");
        res.push_back(e2);
        e3 << AdvancedString("");
        res.push_back(e3);
        res.push_back(e3);
        e4 << AdvancedString("a");
        res.push_back(e4);
        test2(b, res, 55);
    }

    ///////////////////////////////////////////// terminal_rasterize /////////////////////////////////////////////
    {
        AdvancedStringContainer c;
        c << AdvancedString("\nhello worldhow are you today?");
        c << AdvancedString("this is funny stuff\n");
        c << AdvancedString("bye bye world");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e0,e1,e2,e3;
        e << AdvancedString(std::string(17, '-'));
        res.push_back(e);
        e0 << AdvancedString("hello worldhow ar");
        res.push_back(e0);
        e1 << AdvancedString("e you today?this ");
        res.push_back(e1);
        e2 << AdvancedString("is funny stuff..,");
        res.push_back(e2);
        res.push_back(e);
        e3 << AdvancedString("bye bye world...,");
        res.push_back(e3);
        test3(c, res, 17, 71);


    }
    {
        AdvancedStringContainer c;
        c << AdvancedString("\n\nmore and more\n questions arise?");
        c << AdvancedString("due to broken code\n");
        c << AdvancedString("so \nbye bye world\n");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e0,e1,e2,e3,e4,e5;
        e << AdvancedString(std::string(17, '-'));
        res.push_back(e);
        res.push_back(e);
        e0 << AdvancedString("more and more...,");
        res.push_back(e0);
        e1 << AdvancedString(" questions arise?");
        res.push_back(e1);
        e2 << AdvancedString("due to broken cod");
        res.push_back(e2);
        e3 << AdvancedString("e...............,");
        res.push_back(e3);
        res.push_back(e);
        e4 << AdvancedString("so..............,");
        res.push_back(e4);
        e5 << AdvancedString("bye bye world...,");
        res.push_back(e5);
        res.push_back(e);
        test3(c, res, 17, 72);
    }
    {
        AdvancedStringContainer c;
        c << AdvancedString("**this should be colored in MAGENTA**\n", COLOR_MAGENTA);
        c << AdvancedString("**this should be colored in GREEN**\n", COLOR_GREEN);
        c << AdvancedString("----------------------1111111111111111111111111122222222222222222222222222222222233333333333333333333333333333333334444444\n", COLOR_GREEN);
        c << AdvancedString("\n\na");
        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e0,e1,e2,e3,e4,e5;
        e << AdvancedString(std::string(50, '-'));
        e0 << AdvancedString("**this should be colored in MAGENTA**............,");
        res.push_back(e0);
        e1 << AdvancedString("**this should be colored in GREEN**..............,");
        res.push_back(e1);
        e2 << AdvancedString("----------------------1111111111111111111111111122");
        res.push_back(e2);
        e3 << AdvancedString("22222222222222222222222222222223333333333333333333");
        res.push_back(e3);
        e4 << AdvancedString("3333333333333334444444...........................,");
        res.push_back(e4);
        res.push_back(e);
        res.push_back(e);
        e5 << AdvancedString("a................................................,");
        res.push_back(e5);
        test3(c, res, 50, 73);
        std::vector<AdvancedStringContainer> buf;

        AdvancedStringContainer::trimTrailingNewlines(buf, c);
        std::cout << "==== NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN: ====" << std::endl;
        for (int i=0; i < buf.size(); ++i) {
            std::cout  << "'" << YELLOW << buf[i].str() << RESET << "'" << std::endl;
        }
    }
    exit(0);
#endif

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



