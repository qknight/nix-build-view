# motivation

This is an interactive showcase how nix-build could be extended for better
usability using a GUI based on ncurses.

`nix-build` uses perl scripts to download NAR files, these 3 examples implement
a callback which can be used to query the status of such downloads:

* `01-curl-transport.pl`
* `net_curl_easy.pl`
* `www_curl_easy.pl`

In nix-build-view I've written a ncurses based view with advanced color string
handling.

# Outstanding concepts

I wanted to have colored widgets thus I had to write my own `WindowManager` and
I added my own `AdvancedString` implementation. Please feel free to copy them.

Note: `AdvancedString` could need some profiling but it is fast enough for this
purpose.

# Licensing

I'm not sure which license to pick. two options:

* If I merge this source into nix-build i will pick BSD (this is what nix-build
  is licensed to)
* If it is decided that nix-build-view should be 'just a view' and thus be its
  own process GPLv3 would be a good pick

However, I'm open to discussion!

# How to get nix-build-view compiled & running

Note: This repository is called nix-build-view _but_ also contains a directory
called nix-build-view!

Using stdenv (GCC):

```
cd nix-build-view
nix-shell -p ncurses cmake
mkdir build; cd build
cmake ..
make
./nix-build-view
```

In case you want to use clang (LLVM):

```
cd nix-build-view
nix-shell -p ncurses cmake clang
mkdir build; cd build
export CC=clang
export CXX=clang++
cmake ..
make
./nix-build-view
```
