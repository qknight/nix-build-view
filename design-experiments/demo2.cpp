// http://infohost.nmt.edu/~eweiss/222_book/222_book/0201433079/ch18lev1sec12.html
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */

#include <string.h>
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

#include <sys/time.h>
#include <time.h>

#include <errno.h>

using namespace std;

// http://ispltd.org/mini_howto:ansi_terminal_codes
#define CURSOR_SAVE "\e7"
#define CURSOR_RESTORE "\e8"
#define CURSOR_TO_START_OF_LINE "\r"
#define CURSOR_UP_ONE_LINE "\e[A"
#define CURSOR_CLEAR_TO_EOL "\e[K"
#define CURSOR_CLEAN_ALL_AFTERWARDS "\e[J"

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

sig_atomic_t signaled = 1;

struct timeval cur_t;
struct timeval last_t;
struct timeval activity_timer;

static int linecount = 0;
static std::stringstream olds;



//FIXME description needs update
// motivation: std::stringstream must be wrapped since terminal control chars might be arbitrary and to
//             count stringlength they have to be ignored. this is needed for rendering the string to the shell.
// TermCtrl wraps std::string and color=0 means no color; color>0 will be replaced by the colortable entry
class AdvancedString {
public:
    AdvancedString(std::string str, bool isTermCtrl) {
        m_str = str;
        m_isTermCtrl = isTermCtrl;
    }
    AdvancedString(std::string str) {
        m_str = str;
        m_isTermCtrl = true;
    }
    // mode==0 -> BW, mode==1 -> color
    std::string render(int mode) {
        if (mode == 0) // BW rendering
            if (m_isTermCtrl == true) {
                return "";
            }
        return m_str;
    }
private:
    std::string m_str;
    bool m_isTermCtrl;
};

// AdvancedStringList can render to std:string with or without using terminal color codes
class AdvancedStringList {
public:
    //FIXME check the return *this... is this good code?
    AdvancedStringList& operator<<( const std::string& s ) {
        cStrings.push_back(AdvancedString(s, false));
        return *this;
    }
    AdvancedStringList& operator<<( const AdvancedString&  t ) {
        cStrings.push_back(t);
        return *this;
    }
    AdvancedStringList& operator<<( const int&  t ) {
        cStrings.push_back(AdvancedString(std::to_string(t), false));
        return *this;
    }
    std::string str() {
        return render_color(0);
    }
    std::string color_str() {
        return render_color(1);
    }
private:
    std::string render_color(int color) {
        std::stringstream sStream;
        for(int i=0; i < cStrings.size(); ++i) {
            sStream << cStrings[i].render(color);
        }
        return sStream.str();
    }
    std::vector<AdvancedString> cStrings;
};

class Widget {
public:
    std::string render(int width=0);
};

class FetchWidget : public Widget {
private:
    std::string m_name;
    float m_percent;
    int m_bits_per_sec;
public:
    FetchWidget(std::string url, float percent, int bits_per_sec) {
        m_name=url;
        m_percent = percent;
        m_bits_per_sec = bits_per_sec;
    };
    //FIXME this code needs AdvancedStringList rewrite!
    std::string render(int width=0) {
        std::stringstream s;

        int size = m_name.size();
        std::stringstream url_progress;
        float end = m_percent * size;
        url_progress << CYAN << m_name.substr(0, (int)end) << RESET <<  m_name.substr((int)end, size-(int)end);

        s << url_progress.str() << " " << (int)(m_percent*100) << "% " << m_bits_per_sec << "\n";
        olds << std::flush;
        olds << s;
        return s.str();
    }
};

void clearStatus() {
//     printf("\e[%iA", linecount);

// printf("\e[r");
    for (int i=0; i < linecount; i++) {
//         printf("\e[1F");
//         printf(CURSOR_TO_START_OF_LINE);

        printf(CURSOR_UP_ONE_LINE);
//         printf(CURSOR_CLEAR_TO_EOL);
    }
        printf(CURSOR_CLEAN_ALL_AFTERWARDS);
}


void drawStatus(int foo) {
    float fa = (((float)foo/5)*0.8) < 1.0 ? ((float)foo/5)*0.8 : 1.0;
    float fb = (((float)foo/5)*0.5) < 1.0 ? ((float)foo/5)*0.5 : 1.0;
    float fc = (((float)foo/5)*1.7) < 1.0 ? ((float)foo/5)*1.7 : 1.0;
    FetchWidget urlW0("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh1-foobar-1.2.3.nar.xz", fa, 12356);
    FetchWidget urlW1("http://cache.nixos.org/nar/0s57kyi85g7lb9irja3i4q35dv8pi4gh1-foobar-1.2.3.nar.xz .........", fb, 12356);
    FetchWidget urlW2("http://cache.nixos.org/nar/0s57kyi8-foobar-1.2.3.nar.xz ..................................", fc, 12356);

    clearStatus();

    //FIXME this must not be done here! or it will be written a gazillion times on terminal resize!
//     if (foo == 3 || foo == 7 || foo == 10)
//         std::cout << " Download of " << CYAN << "http://cache.nixos.org/nar/00fwcb3janb72b1xf4rnq7ninzmvm8zzzlr6lc8sp9dbl7x838iz.nar.xz" << RESET << " finished\n" <<
//                   "  -> 24.4 Mib in 0:01:25, average speed 115 kib/s\n" <<
//                   "  -> writing  to ‘/nix/store/94l17wjg65wpkwcm4x51pr5dlvarip6a-" << CYAN << "gcc-4.8.2" << RESET << " - " << foo << "’\n";

    AdvancedStringList aout;

    //FIXME found new bug: when amount of lines written exceeds the number of visibile lines it removes a false amount of lines and damages the terminal output
    aout << "-----------------------------\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";

    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";

    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";

    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";

//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
// 
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
// 
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";
//     aout << TermCtrl(MAGENTA) << "building:" << TermCtrl(RESET) << "\n";

    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
    //FIXME long strings will create a problem when being wrapped.... duno where the error is, need to investegate!
    aout << AdvancedString(MAGENTA) << "buildingdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddbuildingdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddbuildingdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddbuildingdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddbuildingdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddbuildingddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd dddd:" << AdvancedString(RESET) << "\n";
    aout << AdvancedString(MAGENTA) << "building:" << AdvancedString(RESET) << "\n";
//     aout << " " << "/nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-" << TermCtrl(MAGENTA) << "gzip-1.6" << TermCtrl(RESET) << " - 2m" << foo+28 << "s " << "\n";
//     aout << "    [ " << TermCtrl(BOLDYELLOW) << "installationPhase" << TermCtrl(RESET) << " ] - /tmp/build-ylcpwyczz887grq8lzdz8hn81q7yrn38/log\n";
//     aout << " " << "/nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-" << TermCtrl(MAGENTA) << "foobar-1.7" << TermCtrl(RESET) << " - 5m" << foo+17 << "s " << "\n";
//     aout << "    [ " << TermCtrl(BOLDYELLOW) << "postinstallationPhase" << TermCtrl(RESET) << " ] - /tmp/build-yczz887grq8lzdylcpwz8hn81q7yrn38/log\n";
    if (foo < 10) aout << AdvancedString(GREEN) <<  "fetching:" << AdvancedString(RESET) << "\n";
    //FIXME the UrlWidget code is not using TermCtrl and AdvancedStringList yet so fix that!
//     if (fa < 1.0) aout << " " << urlW0.render();
//     if (fb < 1.0) aout << " " << urlW1.render();
//     if (fc < 1.0) aout << " " << urlW2.render();
    aout << "=== " << AdvancedString(YELLOW) << "running since 20m" << foo+12 << "s" << AdvancedString(RESET) << " ===" << "\n";

    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");

    std::cout << aout.color_str();

    /////////////<compute lines to remove on redraw>//////////////////////////////////
//     fprintf(stderr, "=====================================\n");

    std::vector<std::string> strings;
    std::string s;
    linecount=0;
    std::stringstream ssout;
    ssout << aout.str(); // to compute the real width, we need the strings without terminal control sequences
    while(std::getline(ssout, s, '\n')) {
        strings.push_back(s);
    }
//     fprintf(stderr, "strings.size()=%i\n", strings.size());
    for(int i=0; i < strings.size(); ++i) {
        int v = strings[i].size()/size.ws_col;
        int r = strings[i].size()%size.ws_col;
        if (v > 0 && r == 0)
            v--;
        linecount+=v;
//         fprintf(stderr, "strings[i].size=%i, i=%i, v=%i, size.ws_col=%i\n", strings[i].size(), i,v, size.ws_col);
//         fprintf(stderr, "%s\n", strings[i].c_str());

    }
    linecount += strings.size();
//     fprintf(stderr, "=====================================\n");
    /////////////</compute lines to remove on redraw>/////////////////////////////////
}

// std::string GetEnv( const string & var ) {
//     const char * val = ::getenv( var.c_str() );
//     if ( val == 0 ) {
//         return "";
//     }
//     else {
//         return val;
//     }
// }

// static void pr_winsize(int fd)
// {
//     struct winsize size;
//
//     if (ioctl(fd, TIOCGWINSZ, (char *) &size) < 0)
//         printf("TIOCGWINSZ error");
//     printf("%d rows, %d columns\n", size.ws_row, size.ws_col);
// }

void signal_callback_handler(int signum) {
    //printf("Caught signal %d\n",signum);

    //std::cout << GetEnv("PATH") << std::endl;
    if (signum == SIGINT)
        signaled = 0;
}


int main() {
    int foo = 0;
    struct winsize size;
    if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
        printf("TIOCGWINSZ error");
    //printf("%d rows, %d columns\n", size.ws_row, size.ws_col);


//<TermCtrl experiments>/////////////////////////////////////////////////////////////
//     AdvancedStringList ad;
//     ad << TermCtrl(RED, "hello world\n");
//     ad << "hello";
//     ad << " world\n";
//     ad << TermCtrl(MAGENTA, "i love you\n");
//     std::cout << ad.color_str() << std::endl;
//     exit(0);
//</TermCtrl experiments>/////////////////////////////////////////////////////////////


    // another test BEGIN
    // this test prooved what i had suspeced, that is: when doing printf to the terminal it will compute line-wrap once
    // but never afterwards. this means that if one writes 3 lines and the console is resized afterwards, it will
    // always be 3 lines needed to be removed. not more not less!
    //
    // 1. execute this program until you can see the 11111____* string on the shell, then quick
    // 2. resize the terminal to 30 cols and afterwards the right amount of cols will be removed
    // 3. also test vice versa, start at 30 cols and then resize it to 130 cols, must have the same effect [tm]
    //
    //std::cout << "==================oben=================\n";

    //std::string s = "11111_____11112_____11113_____11114_____11115_____11116_____11117_____11118_____11119_____11121_____11122_____\n";
    //std::cout << s;
    //sleep(1);

    //int c=0;
    //for(int i=0; i < s.size(); ++i) {
    //  if(s[i] == '\n')
    //    c+=(i/size.ws_col)+1;
    //}

    //while(c--)
    //  printf(CURSOR_UP_ONE_LINE);
    //printf(CURSOR_CLEAN_ALL_AFTERWARDS);
    //std::cout << "==================unten=================\n";
    //pr_winsize(0);
    //std::cout << s.size();

    //exit(1);
    // another test END


    //http://stackoverflow.com/questions/4963421/vt-terminal-disable-local-editing-and-echo
    struct termios term_stored;
    struct termios term_new;
    struct termios term_old;
    tcgetattr(0,&term_stored);
    tcgetattr(0,&term_old);
    memcpy(&term_new,&term_old,sizeof(struct termios));
    term_new.c_lflag &= ~(ECHO|ICANON); /* disable echo and canonization */
    tcsetattr(0,TCSANOW,&term_new);

    //signal(SIGWINCH, signal_callback_handler);

    // https://lwn.net/Articles/176911/
    sigset_t emptyset, blockset;

    sigemptyset(&blockset);         /* Block SIGINT */
    sigaddset(&blockset, SIGINT);
    sigaddset(&blockset, SIGWINCH);
    sigaddset(&blockset, SIGSTOP);
    sigprocmask(SIG_BLOCK, &blockset, NULL);

    struct sigaction sa;
    sa.sa_handler = signal_callback_handler;        /* Establish signal handler */
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGWINCH, &sa, NULL);
    //sigaction(SIGSTART, &sa, NULL);

    std::cout <<
              "building Nix...\n" <<
              "these derivations will be " << MAGENTA << "built" << RESET << ":\n" <<
              "  /nix/store/4hh3935anmmhl13q8lmdkgdsxzh46gq6-" << MAGENTA << "tig-1.1.drv\n" << RESET <<
              "  /nix/store/9brfbp9gk7x3qim52q49rckhw7vw08h2-" << MAGENTA << "asciidoc-8.6.8.drv\n" << RESET <<
              "  /nix/store/ckn6dnnb0ayjbdn3avpqvqa5rs35k2w1-" << MAGENTA << "tig-1.1.tar.gz.drv\n" << RESET <<
              "  /nix/store/j9bgfp4q6h8gdi4b6idvi1r39b5hagvz-" << MAGENTA << "asciidoc-8.6.8.tar.gz.drv\n" << RESET <<
              "these paths will be " << GREEN << "fetched" << RESET << " (40.1 Mib download, 201.66 Mib unpacked):\n" << RESET <<
              "  /nix/store/0yzz6p08k1sgpdb63c0wx48vx0yc51g6-" << GREEN << "bzip2-1.0.6\n" << RESET <<
              "  /nix/store/1a08qk5q5vdfv13rwasbf4fqa2s26kx4-" << GREEN << "attr-2.4.47\n" << RESET <<
              "  /nix/store/3amm865b2qb5s5mwvshvd9kpfq3aj1bc-" << GREEN << "libssh2-1.4.3\n" << RESET <<
              "  /nix/store/5myfmphlck9gcabr6czlg6792d9zhh4m-" << GREEN << "perl-DBI-1.630\n" << RESET <<
              "  /nix/store/j298bijkgdzzv6wlzdidldx297ch5rq2-" << GREEN << "nix-1.7pre3327_0e2ca\n" << RESET <<
              "  /nix/store/mad928szz57gjpbfm9dih23hpspzz11f-" << GREEN << "openssl-1.0.1f\n" << RESET <<
              "  /nix/store/q784x64hp3nwdxx7lbgb16f74i2bhxxk-" << GREEN << "glibc-2.18\n" << RESET <<
              "  /nix/store/qw7vn33jcv1yfsfdw19ic5r2jlqk68w3-" << GREEN << "bash-4.2-p45\n" << RESET <<
              "  /nix/store/skxdffb34mcz50f9q691qsg44bgrxg2x-" << GREEN << "perl-DBD-SQLite-1.37\n" << RESET <<
              "  /nix/store/vmq6nmnvyblnwlrmhhhpnsjdlri4qz25-" << GREEN << "curl-7.33.0\n" << RESET <<
              "  /nix/store/xay7d5hfhm9vj3v31dbzimi08ydrgd4w-" << GREEN << "zlib-1.2.8\n" << RESET <<
              "  /nix/store/xkhr68z09y66c1qwzdq03lnhjl9c51si-" << GREEN << "perl-WWW-Curl-4.15\n" << RESET <<
              "  /nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-" << GREEN << "gzip-1.6\n" << RESET <<
              "  /nix/store/z1krxp2hwph8fypchf2b0ssnyp6z8k9l-" << GREEN << "perl-5.16.3\n" << RESET <<
              "  /nix/store/zp4bcz188h69jvrb1qyl10lfkanz7ld3-" << GREEN << "boehm-gc-7.2d\n" << RESET <<
              "  /nix/store/zsl05mbb69s38bbyi9nfff6vyry9m8jm-" << GREEN << "gnutar-1.27.1\n" << RESET <<
              "  /nix/store/zxvyl58mw530xf811nmm0i8b6nibwmw5-" << GREEN << "coreutils-8.21\n" << RESET <<
              "-----------------------------\n";

    fd_set rfds;
    struct timespec tv;
    int retval;

    gettimeofday(&cur_t, 0);
    gettimeofday(&last_t, 0);
    gettimeofday(&activity_timer, 0);

    /* Watch skt to see when it has input. */
    FD_ZERO(&rfds);
    //FD_SET(skt, &rfds);

    tv.tv_sec = 1;
    tv.tv_nsec = 0;

    while(signaled) {
        // have to use pselect()
        // todo:
        // - pass stdin/stderr through
        // - update status every second
        // - process redraws from the sinal handler AND from each forked and downloading|building child process by using socket writes
        sigemptyset(&emptyset);
        retval = pselect(1, &rfds, NULL, NULL, &tv, &emptyset);

        if (retval < 0) {
            if (errno == EINTR) {
                //printf("signal\n");
                //printf("%lu, %lu\n", tv.tv_sec, tv.tv_nsec);
                drawStatus(foo);
                continue;
            }
            printf("error in pselect\n");
            exit(1);
        }
        // timeout
        if (retval == 0) {
            drawStatus(foo);
            if(foo==10) {
                //clearStatus();
                exit(0);
            }
            foo+=1;

            tv.tv_sec = 1;
            tv.tv_nsec = 0;

            // resetting this is mendatory (see manpage: man 2 select)
            FD_ZERO(&rfds);
            //FD_SET(skt, &rfds);
        }

        // process FDs since data is there
        // see http://publib.boulder.ibm.com/infocenter/iseries/v5r3/index.jsp?topic=%2Frzab6%2Frzab6xnonblock.htm
        if (retval > 0) {

        }
    }
    tcsetattr(0,TCSANOW,&term_stored); /* restore the original state */
}





