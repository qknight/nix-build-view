#ifndef TERMINALWIDGET__HPP
#define TERMINALWIDGET__HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "Widget.hpp"


class TerminalWidget : public Widget {
public:
    TerminalWidget();
    void splitString(std::vector<std::string> &v_str,const std::string &str,const char ch);
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    void append(AdvancedStringContainer line);
    void terminal_rasterize();
    int type();
    void keyboardInputHandler(int ch);
    AdvancedStringContainer log() {
        return m_logfile;
    };
private:
    AdvancedStringContainer m_logfile;
    unsigned int m_line = 0;
    std::vector<std::string> m_terminal;
};

#endif
