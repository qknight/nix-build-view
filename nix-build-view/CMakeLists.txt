cmake_minimum_required(VERSION 2.8)
FIND_PACKAGE(Curses)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(nix-build-view_SOURCES ${nix-build-view_SOURCES}
  nix-build-view.cpp
  Layout.cpp 
  WindowManager.cpp 
  TerminalWidget.cpp 
  StatusWidget.cpp 
  FetchWidget.cpp 
  BuildWidget.cpp 
  ColorManager.cpp 
  HelpWidget.cpp 
  VerticalSpacerWidget.cpp 
  BuildWidgetManager.cpp 
  FetchWidgetManager.cpp 
  WidgetManagerBase.cpp 
  TDD-nix-build.cpp
)

SET(TDD-AdvancedString_SOURCES ${TDD-AdvancedString_SOURCES}
  TDD-AdvancedStringTest.cpp
)

#-std=c++0x or -std=gnu++0x
ADD_DEFINITIONS("-std=c++11")
#ADD_DEFINITIONS("-O0")

ADD_DEFINITIONS("-Wall")

ADD_EXECUTABLE ( TDD-AdvancedStringTest ${TDD-AdvancedString_SOURCES})

if (CURSES_FOUND)
    ADD_EXECUTABLE ( nix-build-view ${nix-build-view_SOURCES})

    TARGET_LINK_LIBRARIES( nix-build-view ${CURSES_LIBRARIES})

    INCLUDE_DIRECTORIES(
      ${CURSES_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
    )

    TARGET_LINK_LIBRARIES ( nix-build-view ncurses)
    INSTALL ( TARGETS nix-build-view DESTINATION bin )

else (CURSES_FOUND)
    MESSAGE(FATAL_ERROR "ncurses library not found, can't build nix-build-view then!") 
endif (CURSES_FOUND)


