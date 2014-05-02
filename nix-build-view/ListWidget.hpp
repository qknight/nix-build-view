#ifndef LISTWIDGET__HPP
#define LISTWIDGET__HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "Widget.hpp"


class ListWidget : public Widget {
public:
    ListWidget();
    void splitString(std::vector<std::string> &v_str,const std::string &str,const char ch);
    AdvancedStringContainer render();
    void append(AdvancedStringContainer line);
    void resize(unsigned int w, unsigned int h);
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
//     unsigned int m_width_last = 0;
//     unsigned int m_height_last = 0;
};

#endif
