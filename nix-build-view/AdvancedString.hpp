#ifndef ADVANCEDSTRING_HPP
#define ADVANCEDSTRING_HPP

#include "ColorCodes.h"

/*
 * motivation for AdvancedStringContainer was that each terminal (xterm, vt100, ncurses) do interprete escape sequences differently
 *
 * my requirements were:
 *  - i need to be able to count the amount of chars (without color escape sequences) to predict if the string fits into the given widget's width
 *  - to print the string to a normal xterm with colors while
 *  - also using the same representation to draw it using ncurses
 */
class AdvancedString {
public:
    AdvancedString(std::string color, std::string string) {
        m_str = string;
        m_color = color;
    }
    AdvancedString(std::string string) {
        m_str = string;
        m_color = "";
    }
    int size() {
        return m_str.size();
    }
    std::string str() {
        return render(0);
    }
    // mode==0 -> BW, mode==1 -> color
    std::string render(int mode) {
        if (mode == 0) // BW rendering
            return  m_str;
        return m_color + m_str + RESET;
    }
private:
    std::string m_str;
    std::string m_color;
};

// AdvancedStringList can render to std:string with or without using terminal color codes
class AdvancedStringContainer {
public:
    AdvancedStringContainer& operator<<( const std::string& s1 ) {
        sContainer.push_back(AdvancedString("", s1));
        return *this;
    }
    AdvancedStringContainer& operator<<( const AdvancedString&  t ) {
        sContainer.push_back(t);
        return *this;
    }
    AdvancedStringContainer& operator<<( const int&  t ) {
        sContainer.push_back(AdvancedString(std::to_string(t), ""));
        return *this;
    }
    std::string str() {
        return render_color(0);
    }
    std::string terminal_str() {
        return render_color(1);
    }
    const std::vector<AdvancedString>data() {
        return sContainer;
    }
    // string size (which ignores the terminal control sequences like colors, but contains things like '\n' and '\t')
    int size() {
        int s=0;
        for(int i=0; i < sContainer.size(); ++i) {
            s += sContainer[i].size();
        }
        return s;
    }

private:
    std::string render_color(int color) {
        std::stringstream sStream;
        for(int i=0; i < sContainer.size(); ++i) {
            sStream << sContainer[i].render(color);
        }
        return sStream.str();
    }
    std::vector<AdvancedString> sContainer;
};

#endif
