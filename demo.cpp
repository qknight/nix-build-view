#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */


using namespace std;

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

sig_atomic_t signaled = 0;

void my_handler (int param)
{
    signaled = 1;
}

static int linecount = 0;

class Widget {
public:
    std::string render();
};

class UrlWidget : public Widget {
private:
    std::string m_url;
    float m_percent;
    int m_bits_per_sec;
public:
    UrlWidget(std::string url, float percent, int bits_per_sec) {
        m_url=url;
        m_percent = percent;
        m_bits_per_sec = bits_per_sec;
    };
    std::string render() {
        std::stringstream s;

        int size = m_url.size();
        std::stringstream url_progress;
        float end = m_percent * size;
        url_progress << CYAN << m_url.substr(0, (int)end) << RESET <<  m_url.substr((int)end, size-(int)end);

        s << url_progress.str() << " " << (int)(m_percent*100) << "% " << m_bits_per_sec << "\n";
        return s.str();
    }
};

void clearStatus() {
    for (int i=0; i < linecount; i++) {
        //printf(CURSOR_TO_START_OF_LINE);
        printf(CURSOR_UP_ONE_LINE);
        //printf(CURSOR_CLEAR_TO_EOL);
    }
    printf(CURSOR_CLEAN_ALL_AFTERWARDS);
}


void drawStatus(int foo) {
    float fa = (((float)foo/5)*0.8) < 1.0 ? ((float)foo/5)*0.8 : 1.0;
    float fb = (((float)foo/5)*0.5) < 1.0 ? ((float)foo/5)*0.5 : 1.0;
    float fc = (((float)foo/5)*1.7) < 1.0 ? ((float)foo/5)*1.7 : 1.0;
    UrlWidget urlW0("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh1-foobar-1.2.3.nar.xz", fa, 12356);
    UrlWidget urlW1("http://cache.nixos.org/nar/0s57kyi85g7lb9irja3i4q35dv8pi4gh1-foobar-1.2.3.nar.xz .........", fb, 12356);
    UrlWidget urlW2("http://cache.nixos.org/nar/0s57kyi8-foobar-1.2.3.nar.xz ..................................", fc, 12356);

    clearStatus();
    if (foo == 3 || foo == 7 || foo == 10) 
    std::cout << " Download of " << CYAN << "http://cache.nixos.org/nar/00fwcb3janb72b1xf4rnq7ninzmvm8zzzlr6lc8sp9dbl7x838iz.nar.xz" << RESET << " finished\n" <<
              "  -> 24.4 Mib in 0:01:25, average speed 115 kib/s\n" <<
              "  -> writing  to ‘/nix/store/94l17wjg65wpkwcm4x51pr5dlvarip6a-" << CYAN << "gcc-4.8.2" << RESET << "’\n";

    std::stringstream ssout;
    ssout << "-----------------------------\n";
    ssout << MAGENTA << "building:" << RESET << "\n";
    ssout << " " << "/nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-" << MAGENTA << "gzip-1.6" << RESET << " - 5 min " << foo << " sec" << "\n";
    if (foo < 10) ssout << GREEN << "fetching:" << RESET << "\n";
    if (fa < 1.0) ssout << " " << urlW0.render();
    if (fb < 1.0) ssout << " " << urlW1.render();
    if (fc < 1.0) ssout << " " << urlW2.render();

    std::string sout = ssout.str();
    std::cout << sout;
    int c = 0;
    for (int i=0 ;  i <= sout.size(); ++i)
        if (sout[i] == '\n')
            c++;
    linecount = c;
}


void signal_callback_handler(int signum) {
    printf("Caught signal %d\n",signum);

    exit(signum);
}


int main() {
    int foo = 0;
    signal(SIGWINCH, signal_callback_handler);

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

    while(1) {
        drawStatus(foo);
        if(foo==10) {
//             clearStatus();
            exit(0);
        }
        foo+=1;
        sleep(1);
    }
}

