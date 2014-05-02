#CC=clang++
CC=g++
CFLAGS=-c -Wall -std=c++11 -I /usr/include
LDFLAGS=
LIBS=-lncurses
SOURCES=nix-build-view.cpp WindowManager.cpp ListWidget.cpp StatusWidget.cpp UrlWidget.cpp BuildWidget.cpp ColorManager.cpp HelpWidget.cpp
DEPS=AdvancedString.hpp ColorManager.hpp ListWidget.hpp UrlWidget.hpp WindowManager.hpp BuildWidget.hpp HelpWidget.hpp StatusWidget.hpp Widget.hpp


OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=nix-build-view

all: clean $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f *.o nix-build-view core
