#include <stdio.h>
#include <unistd.h>

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

int update(int foo) {
  int i=0;
  if (foo != 0) {
    for (i=0; i < 8; i++) {
      printf(CURSOR_TO_START_OF_LINE);
      printf(CURSOR_UP_ONE_LINE); 
      //printf(CURSOR_CLEAR_TO_EOL);
    }
    printf(CURSOR_CLEAN_ALL_AFTERWARDS);
  }
  printf("some log line %i\n", foo);
  printf("----------------------------------------------\n");

  //if (foo != 5)
printf("[0;0;35mbuilding:[0;33;0m  \n"
" /nix/store/ylcpwyczz887grq8lzdz8hn81q7yrn38-[0;0;35mgzip-1.6[0;33;0m\n"
" /nix/store/j298bijkgdzzv6wlzdidldx297ch5rq2-[0;0;35mnix-1.7pre3327_0e2ca26[0;33;0m\n"
"[0;0;32mfetching:[0;33;0m \n"
" [0;0;36mhttp://cache.nixos.org/nar/0s57kyi85g7lb9irja2csl[0;33;0mmh5vc23i4q35dv8pi4gh19k0jc7nf3.nar.xz [0;0;33m 50% - 1.82 M/s[0;33;0m\n"
" [0;0;36mhttp://cache.nixos.org/nar/0s57kyi85g7lb9irja2cslmh5vc23i4q35dv8pi4g[0;33;0mh19k0jc7nf3.nar.xz [0;0;33m 70% - 10.25 M/s[0;33;0m\n"
" [0;0;36mhttp://cache.nixos.org/nar/0s55vc23i4q35dv8pi4g[0;33;0mh19k0jc7nf3.nar.xz..................... [0;0;33m 49% - %u 0.25 M/s[0;33;0m\n", foo);
}

int main() {
  int foo = 0;
  printf("---------------------------------------------\n");
  while(1) {
    update(foo);
    if(foo==5)
      exit(0);
    foo+=1;
    sleep(1);
  }
}

