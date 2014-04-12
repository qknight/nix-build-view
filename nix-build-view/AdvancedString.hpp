#ifndef ADVANCEDSTRING_HPP
#define ADVANCEDSTRING_HPP

#include "Colorcodes.h"

/*
 * motivation for AdvancedStringList was that each terminal (xterm, vt100, ncurses) do interprete escape sequences differently
 * 
 * my requirements were:
 *  - i need to be able to count the amount of chars (without color escape sequences) to predict if the string fits into the given widget's width
 *  - to print the string to a normal xterm with colors while
 *  - also using the same representation to draw it using ncurses 
 */ 
class TermCtrl {
public:
    TermCtrl(std::string str, bool isTermCtrl) {
        m_str = str;
        m_isTermCtrl = isTermCtrl;
    }
    TermCtrl(std::string str) {
        m_str = str;
        m_isTermCtrl = true;
    }
    // mode==0 -> BW, mode==1 -> color
    std::string render(int mode) {
        if (mode == 0) // BW rendering
            if (m_isTermCtrl == true) {
                return "";
            }
        return m_str;
    }
private:
    std::string m_str;
    bool m_isTermCtrl;
};

// AdvancedStringList can render to std:string with or without using terminal color codes
class AdvancedStringList {
public:
    //FIXME check the return *this... is this good code?
    AdvancedStringList& operator<<( const std::string& s ) {
        cStrings.push_back(TermCtrl(s, false));
        return *this;
    }
    AdvancedStringList& operator<<( const TermCtrl&  t ) {
        cStrings.push_back(t);
        return *this;
    }
    AdvancedStringList& operator<<( const int&  t ) {
        cStrings.push_back(TermCtrl(std::to_string(t), false));
        return *this;
    }
    std::string str() {
        return render_color(0);
    }
    std::string color_str() {
        return render_color(1);
    }
private:
    std::string render_color(int color) {
        std::stringstream sStream;
        for(int i=0; i < cStrings.size(); ++i) {
            sStream << cStrings[i].render(color);
        }
        return sStream.str();
    }
    std::vector<TermCtrl> cStrings;
};

#endif