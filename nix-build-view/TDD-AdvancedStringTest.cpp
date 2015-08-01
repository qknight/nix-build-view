#include <vector>
#include <iostream>
#include <sstream>
#include <AdvancedString.hpp>

void
test1(AdvancedStringContainer& a,
      std::vector<AdvancedStringContainer> res,
      int num)
{
    std::vector<AdvancedStringContainer> t;
    AdvancedStringContainer::containerStringSplit(t, a, '\n');

    bool r = true;

    if (t.size() != res.size()) {
        r = false;
    }

    if (r) {
        for (int i=0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r = false;
                break;
            }
        }
    }

    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST containerStringSplit----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "result was:" << std::endl;

        for (int i = 0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }

        std::cout <<   "but should be:" <<  std::endl;

        for (int i = 0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }

        std::cout << YELLOW << "---------------------------END TEST containerStringSplit----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

void
test2(AdvancedStringContainer& a,
      std::vector<AdvancedStringContainer> res,
      int num)
{
    std::vector<AdvancedStringContainer> t;
    AdvancedStringContainer::trimEndAndRemoveNewlineChars(t, a);

    bool r = true;

    if (t.size() != res.size()) {
        r = false;
    }

    if (r) {
        for (int i = 0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r = false;
                break;
            }
        }
    }

    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST trimEndAndRemoveNewlineChars----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "==== input was: ====" << std::endl;

        for (int i = 0; i < a.size(); ++i) {
            std::cout << "'" << YELLOW << a[i].str() << RESET << "'" << std::endl;
        }

        std::cout << "==== result was: ====" << std::endl;

        for (int i = 0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }

        std::cout <<   "==== but should be: ====" <<  std::endl;

        for (int i = 0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }

        std::cout << YELLOW << "---------------------------END TEST trimEndAndRemoveNewlineChars----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

void
test3(AdvancedStringContainer& a,
      std::vector<AdvancedStringContainer> res,
      int width,
      int num)
{
    std::vector<AdvancedStringContainer> t;

    AdvancedStringContainer::terminal_rasterize(t, a, width);

    bool r = true;

    if (t.size() != res.size()) {
        r = false;
    }

    if (r) {

        for (int i = 0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r = false;
                break;
            }
        }
    }

    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST terminal_rasterize----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "==== input was: ====" << std::endl;

        for (int i = 0; i < a.size(); ++i) {
            std::cout  << "'" << YELLOW << a[i].str() << RESET << "'" << std::endl;
        }

        std::cout << "==== result was: ====" << std::endl;

        for (int i = 0; i < t.size(); ++i) {
            std::cout  << "'" << RED << t[i].str() << RESET << "'" << std::endl;
        }

        std::cout <<   "==== but should be: ====" <<  std::endl;

        for (int i = 0; i < res.size(); ++i) {
            std::cout << "'" << GREEN << res[i].str() << RESET <<"'" << std::endl;
        }

        std::cout << YELLOW << "---------------------------END TEST terminal_rasterize----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

void
test4(AdvancedString& a,
      AdvancedString& res,
      unsigned int b,
      unsigned int len,
      int num)
{
    AdvancedString t    = AdvancedString::substr(a, b, len);
    bool r              = true;

    if (t.size() != res.size()) {
        r = false;
    }

    if (r) {
        for (int i=0; i < t.size(); ++i) {
            if (t.str() != res.str()) {
                r = false;
                break;
            }
        }
    }

    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST AdvancedString::substr ----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;
        std::cout << "==== input was: ====" << std::endl;
        std::cout  << "'" << YELLOW << a.str() << RESET << "'" << std::endl;
        std::cout << "==== result was: ====" << std::endl;
        std::cout  << "'" << RED << t.str() << RESET << "'" << std::endl;
        std::cout <<   "==== but should be: ====" <<  std::endl;
        std::cout << "'" << GREEN << res.str() << RESET <<"'" << std::endl;
        std::cout << YELLOW << "---------------------------END TEST AdvancedString::substr ----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

void
test5(AdvancedStringContainer& a,
      AdvancedStringContainer& res,
      int b,
      int len,
      int num)
{
    AdvancedStringContainer t;

    AdvancedStringContainer::substr(t, a, b, len);

    bool r = true;
    bool s = true;

    if (t.size() != res.size()) {
        r = false;
        s = false;
    }

    if (r) {
        for (int i = 0; i < t.size(); ++i) {
            if (t[i].str() != res[i].str()) {
                r = false;
                break;
            }
        }
    }

    if (!r) {
        std::cout << YELLOW << "---------------------------BEGIN TEST AdvancedStringContainer::substr ----------------------------------------------" << RESET << std::endl;
        std::cout << RED << "TEST " << num << " WAS A FAILURE" << RESET << std::endl;

        if (!s) {
            std::cout << RED << "size difference in AdvancedStringContainer t vs res =  " << t.size() << " vs " << res.size() << RESET << std::endl;
        }

        std::cout << "==== input was: ====" << std::endl;
        std::cout  << "'" << YELLOW << a.str() << RESET << "'" << std::endl;

        std::cout << "==== result was: ====" << std::endl;
        std::cout  << "'" << RED << t.str() << RESET << "'" << std::endl;

        std::cout <<   "==== but should be: ====" <<  std::endl;
        std::cout << "'" << GREEN << res.str() << RESET <<"'" << std::endl;

        std::cout << YELLOW << "---------------------------END TEST AdvancedStringContainer::substr ----------------------------------------------" << RESET << std::endl<< std::endl<< std::endl;
    }
}

int
main(int argc, char *argv[])
{
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
        a << AdvancedString("\n11akf__\n__jaffka22")
          << AdvancedString("33akfkafk44\n55asdkfasdfk66")
          << AdvancedString("\n77afafaf88\n\n\nf");

        std::vector<AdvancedStringContainer> res;

        AdvancedStringContainer e, e1, e2, e3, e4, e5, e6, e7;
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
        AdvancedStringContainer a;
        a << AdvancedString("**this should be colored in MAGENTA**\n", COLOR_MAGENTA);
        a << AdvancedString("**this should be colored in GREEN**\n", COLOR_GREEN);
        a << AdvancedString("----------------------1111111111111111111111111122222222222222222222222222222222233333333333333333333333333333333334444444\n", COLOR_GREEN);
        a << AdvancedString("\n\na");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e, e1, e2, e3, e4;

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

        test1(a, res, 11);
    }

    {
        AdvancedStringContainer a;
        a << AdvancedString("  foo\n");
        a << AdvancedString(" bar  ");
        a << AdvancedString("   ");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e,e1;
        e << AdvancedString("  foo");
        res.push_back(e);

        e1 << AdvancedString(" bar  ");
        e1 << AdvancedString("   ");
        res.push_back(e1);

        test1(a, res, 12);
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

    {
        AdvancedStringContainer b;
        b << AdvancedString("  foo\n");
        b << AdvancedString(" bar  ");
        b << AdvancedString("   ");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e1,e2;
        e1 << AdvancedString("  foo");
        res.push_back(e1);

        e2 << AdvancedString(" bar");
        res.push_back(e2);

        test2(b, res, 56);
    }

    {
        AdvancedStringContainer b;
        b << AdvancedString("123  \n");
        b << AdvancedString("  \n");
        b << AdvancedString("1lk2j312k3j");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e1,e2,e3;

        e1 << AdvancedString("123");
        res.push_back(e1);

        e2 << AdvancedString("");
        res.push_back(e2);

        e3 << AdvancedString("1lk2j312k3j");
        res.push_back(e3);

        test2(b, res, 57);
    }

    ////////////////////////// terminal_rasterize ///////////////////////

    {
        AdvancedStringContainer c;
        c << AdvancedString("\nhello worldhow are you today?");
        c << AdvancedString("this is funny stuff\n");
        c << AdvancedString("bye bye world");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e, e0, e1, e2, e3;

        e << AdvancedString(std::string(17, ' '));
        res.push_back(e);

        e0 << AdvancedString("hello worldhow ar");
        res.push_back(e0);

        e1 << AdvancedString("e you today?this ");
        res.push_back(e1);

        e2 << AdvancedString("is funny stuff   ");
        res.push_back(e2);

        e3 << AdvancedString("bye bye world    ");
        res.push_back(e3);

        test3(c, res, 17, 71);
    }

    {
        AdvancedStringContainer c;
        c << AdvancedString("\n\nmore and more\n questions arise?");
        c << AdvancedString("due to broken code\n\n");
        c << AdvancedString("so \nbye bye world\n");

        std::vector<AdvancedStringContainer> res;
        AdvancedStringContainer e, e0, e1, e2, e3, e4, e5;

        e << AdvancedString(std::string(17, ' '));
        res.push_back(e);
        res.push_back(e);

        e0 << AdvancedString("more and more    ");
        res.push_back(e0);

        e1 << AdvancedString(" questions arise?");
        res.push_back(e1);

        e2 << AdvancedString("due to broken cod");
        res.push_back(e2);

        e3 << AdvancedString("e                ");
        res.push_back(e3);
        res.push_back(e);

        e4 << AdvancedString("so               ");
        res.push_back(e4);

        e5 << AdvancedString("bye bye world    ");
        res.push_back(e5);
//         res.push_back(e);

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

        e << AdvancedString(std::string(50, ' '));
        e0 << AdvancedString("**this should be colored in MAGENTA**             ");
        res.push_back(e0);

        e1 << AdvancedString("**this should be colored in GREEN**               ");
        res.push_back(e1);

        e2 << AdvancedString("----------------------1111111111111111111111111122");
        res.push_back(e2);

        e3 << AdvancedString("22222222222222222222222222222223333333333333333333");
        res.push_back(e3);

        e4 << AdvancedString("3333333333333334444444                            ");
        res.push_back(e4);
        res.push_back(e);
        res.push_back(e);

        e5 << AdvancedString("a                                                 ");
        res.push_back(e5);

        test3(c, res, 50, 73);
        std::vector<AdvancedStringContainer> buf;

//         AdvancedStringContainer::trimEndAndRemoveNewlineChars(buf, c);
//         std::cout << "==== NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN: ====" << std::endl;
//         for (int i=0; i < buf.size(); ++i) {
//             std::cout  << "'" << YELLOW << buf[i].str() << RESET << "'" << std::endl;
//         }
    }

    ////////////////////////// AdvancedString::substr //////////////////////

    {
        AdvancedString c("hello world");
        AdvancedString res("hello");
        test4(c, res, 0, 5, 90);
    }

    {
        AdvancedString c("hello world");
        AdvancedString res("");
        test4(c, res, 0, 0, 91);
    }

    {
        AdvancedString c("hello world");
        AdvancedString res(" world");
        test4(c, res, 5, 55, 92);
    }

    {
        AdvancedString c("hello world");
        AdvancedString res("");
        test4(c, res, 55, 55, 93);
    }

    {
        AdvancedString c("");
        AdvancedString res("");
        test4(c, res, 55, 55, 94);
    }

    {
        AdvancedString c("123");
        AdvancedString res("2");
        test4(c, res, 1, 1, 95);
    }

    //////////////////// AdvancedStringContainer::substr ///////////////////

    {
        AdvancedStringContainer c;
        c << "hello world" << ", how are " << "you";

        AdvancedStringContainer res;
        res << "hello world";

        test5(c, res, 0, 11, 110);
    }

    {
        AdvancedStringContainer c;
        c << "hello world" << ", how are " << "you";

        AdvancedStringContainer res;
        res << "llo world, how";

        test5(c, res, 2, 14, 111);
    }

    {
        AdvancedStringContainer c;
        c << "hello world" << ", how are " << "you";

        AdvancedStringContainer res;
        res << "llo world, how are y";

        test5(c, res, 2, 20, 112);
    }

    {
        AdvancedStringContainer c;
        c << "" << "hello world" << "" << ", how are " << "you";

        AdvancedStringContainer res;
        res << "llo world, how are y";

        test5(c, res, 2, 20, 113);
    }

    {
        AdvancedStringContainer c;
        c << "";

        AdvancedStringContainer res; // should be empty

        test5(c, res, 0, 11, 114);
    }

    {
        AdvancedStringContainer c;
        c << "" << "" << "";

        AdvancedStringContainer res; // should be empty

        test5(c, res, 0, 11, 115);
    }

    {
        AdvancedStringContainer c;
        c << "" << "" << "" << "f" << "";

        AdvancedStringContainer res;
        res << "f";

        test5(c, res, 0, 1, 116);
    }

    exit(0);
}

