#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t *
/* specification
 * builder 5/53 build jobs
 *
 * fetching  5/23 active downloads,  sum of downloads == 23.26 Mbit/s
 *  http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz 50% 23Mib - 1.82 Mbit/s
 *  - shows a progressbar using coloring
 *  - is dynamically generated from a download context
 *  - maxium of 5 downloads is shown
 *  - fastest download is topmost
 *  - summary is also shown
 */

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
        url_progress << GREEN << m_url.substr(0, (int)end) << RESET <<  m_url.substr((int)end, size-(int)end);

        s << url_progress.str() << " " << (int)(m_percent*100) << "% " << m_bits_per_sec << "\n";
        return s.str();
    }
};


void drawStatus(int foo) {
    UrlWidget urlW0("http://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4gh1-foobar-1.2.3.nar.xz", (float)foo/5, 12356);
    UrlWidget urlW1("http://cache.nixos.org/nar/0s57kyi85g7lb9irja3i4q35dv8pi4gh1-foobar-1.2.3.nar.xz .........", (float)foo/5, 12356);
    UrlWidget urlW2("http://cache.nixos.org/nar/0s57kyi8-foobar-1.2.3.nar.xz ..................................", (float)foo/5, 12356);
    static int linecount = 0;

    for (int i=0; i < linecount; i++) {
        //printf(CURSOR_TO_START_OF_LINE);
        printf(CURSOR_UP_ONE_LINE);
        //printf(CURSOR_CLEAR_TO_EOL);
    }
    printf(CURSOR_CLEAN_ALL_AFTERWARDS);
    printf("some log line %i \n", foo);

    std::stringstream ssout;
    ssout << "-----------------------------\n";
    ssout << urlW0.render() << urlW1.render() << urlW2.render();

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
    // Cleanup and close up stuff here
    int rows=system("tput rows");
    int columns=system("tput cols");
    printf("rows= %i, cols = %i\n", rows, columns);

    exit(signum);
}


int main() {
    int foo = 0;
    signal(SIGWINCH, signal_callback_handler);

    int rows=system("tput rows");
    int columns=system("tput cols");
    printf("rows= %i, cols = %i\n", rows, columns);

    printf("---------------------------------------------\n");
    while(1) {
//     update(foo);
        drawStatus(foo);
        if(foo==5)
            exit(0);
        foo+=1;
        sleep(1);
    }
}

