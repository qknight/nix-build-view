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
    void splitString(std::vector<std::string> &v_str,const std::string &str,const char ch);
    std::string render(int w, int h);
    void append(std::string line);
    std::string terminal_preprocess();
    void up();
    void down();
    void pgup();
    void pgdown();
    void home();
    void end();
    std::string log() { return m_logfile.str(); };
private:
    std::stringstream m_logfile;
    int m_line = 0;
    std::vector<std::string> m_terminal;
};

#endif
