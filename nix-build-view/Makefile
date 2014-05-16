#CC=clang++
CC=g++
CFLAGS=-c -Wall -std=c++11 -I /usr/include
LDFLAGS=
LIBS=-lncurses
SOURCES=nix-build-view.cpp Layout.cpp WindowManager.cpp TerminalWidget.cpp StatusWidget.cpp FetchWidget.cpp BuildWidget.cpp ColorManager.cpp HelpWidget.cpp VerticalSpacerWidget.cpp BuildWidgetManager.cpp FetchWidgetManager.cpp WidgetManagerBase.cpp


OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=nix-build-view

all: clean $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@

.cpp.o: $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm -f *.o nix-build-view core
