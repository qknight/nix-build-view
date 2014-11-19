# motivation

this is an interactive showcase how nix-build could be extended for better usability using a GUI based on ncurses.

nix-build uses perl scripts to download NAR files, these 3 examples implement a callback which can be used to query the status of such downloads:

* 01-curl-transport.pl
* net_curl_easy.pl
* www_curl_easy.pl

in nix-build-view i've written a ncurses based view with advanced color string handling.

# outstanding concepts

i wanted to have colored widgets thus i had to write my own WindowManager and i added my own AdvancedString implementation. 
please feel free to copy them.

note: AdvancedString could need some profiling but it is fast enough for this purpose.

# licensing

i'm not sure which license to pick. two options:

* if i merge this source into nix-build i will pick BSD (this is what nix-build is licensed to)
* if it is decided that nix-build-view should be 'just a view' and thus be its own process GPLv3 would be a good pick 

however, i'm open to dicussion!

# how to get this running

 1. cd nix-build-view
 2. nix-shell -p ncurses -p cmake
 3. mkdir build; cd build; cmake ..; 
 4. make
 5. ./nix-build-view

# screenshots

or look at this screenshot(s):

![screenshot1](https://raw.github.com/qknight/nix-build-hack/master/screenshot1.jpeg)

![screenshot2](https://raw.github.com/qknight/nix-build-hack/master/screenshot2.jpeg)

![screenshot3](https://raw.github.com/qknight/nix-build-hack/master/screenshot3.jpeg)

![screenshot4](https://raw.github.com/qknight/nix-build-hack/master/screenshot4.jpeg)
