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
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    void append(AdvancedStringContainer line);
    void terminal_rasterize(std::vector<AdvancedStringContainer> &terminal, int width);
    int type();
    void keyboardInputHandler(int ch);
    AdvancedStringContainer log() {
        return m_logfile;
    };
    static TerminalWidget* Instance();
private:
    AdvancedStringContainer m_logfile;
    int m_line = 0;
    std::vector<AdvancedStringContainer> m_terminal;
    unsigned int width() {
        return m_width;
    }
    unsigned int height() {
        return m_height;
    }
    unsigned int m_width = 0;
    unsigned int m_height = 0;
};

#endif
