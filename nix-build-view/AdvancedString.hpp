#ifndef ADVANCEDSTRING_HPP
#define ADVANCEDSTRING_HPP

#include "ncurses.h"

#include <string>

class AdvancedString {
public:
    AdvancedString() {}
    AdvancedString(std::string string, int color=COLOR_WHITE, int attributes = 0, int bgColor=COLOR_BLACK) {
        m_str = string;
        m_fontColor = color;
        m_attributes = attributes;
        m_bgColor = bgColor;
    }
    int size() {
        return m_str.size();
    }
    std::string str() {
        return m_str;
    }
    int fontColor() {
        return m_fontColor;
    }
    int bgColor() {
        return m_bgColor;
    }
    int attributes() {
        return m_attributes;
    }
private:
    std::string m_str;
    int m_fontColor;
    int m_bgColor;
    int m_attributes;
};

/*
 * main motivation for AdvancedStringContainer:
 * - each Widget should only return a sequence of chars which are then drawn by the WindowManager
 * - this prevents that every widget has full draw support to the whole screen
 * - however, still every widget can use all the formating extensions like color, bold and italic text
 *
 * my requirements were:
 *  - i need to be able to count the amount of chars (without color escape sequences) to predict if the string fits into the given widget's width
 *  - to print the string to a normal xterm with colors while
 *  - also using the same representation to draw it using ncurses
 */
class AdvancedStringContainer {
public:
    AdvancedStringContainer& operator<<( const AdvancedString&  t ) {
        sContainer.push_back(t);
        return *this;
    }
    //FIXME understand why adding const before AdvancedStringContainer results in a strange compiler error
    AdvancedStringContainer& operator<<(  AdvancedStringContainer& c ) {
        for(unsigned int i=0; i < c.size(); ++i) {
            sContainer.push_back(c[i]);
        }
        return *this;
    }
    AdvancedStringContainer& operator<<( const std::string& s1 ) {
        sContainer.push_back(AdvancedString(s1));
        return *this;
    }
    AdvancedStringContainer& operator<<( const int& t ) {
        sContainer.push_back(AdvancedString(std::to_string(t)));
        return *this;
    }
    AdvancedStringContainer& operator<<( const size_t&  t ) {
        sContainer.push_back(AdvancedString(std::to_string(t)));
        return *this;
    }
    AdvancedStringContainer& operator<<( const unsigned int&  t ) {
        sContainer.push_back(AdvancedString(std::to_string(t)));
        return *this;
    }
    AdvancedStringContainer& operator<<( const float&  f ) {
        sContainer.push_back(AdvancedString(std::to_string(f)));
        return *this;
    }
    AdvancedString operator[] (unsigned int element) {
        if (element < sContainer.size())
            return sContainer[element];
        else
            return AdvancedString();
    }
    unsigned int size() {
        return sContainer.size();
    }
    int str_size() {
        unsigned int size = 0;
        for(unsigned int i=0; i < sContainer.size(); ++i) {
            size += sContainer[i].size();
        }
        return size;
    }
    std::string str() {
        std::string s;
        for(unsigned int i=0; i < sContainer.size(); ++i) {
            s += sContainer[i].str();
        }
        return s;
    }
    void clear() {
        sContainer.clear();
    }
    void containerStringSplit(std::vector<AdvancedStringContainer> &v_str, const char ch) {
//         std::vector<AdvancedStringContainer> zzz;
        AdvancedStringContainer tmp;
        for (int i=0; i < this->size(); i++) {
            AdvancedString as = (*this)[i];
            std::string str = as.str();
            std::string sub;
            std::string::size_type pos = 0;
            std::string::size_type old_pos = 0;
            bool flag=true;

            while(flag) {
                pos=str.find_first_of(ch,pos);
                if(pos == std::string::npos)
                {
                    flag = false;
                    pos = str.size();
                }
                sub = str.substr(old_pos,pos-old_pos);  // Disregard the '.'
                tmp << AdvancedString(sub, as.fontColor(), as.attributes(), as.bgColor());
                if (pos != str.size() || i == this->size()-1) {
                    if(tmp.str_size() > 0)
                        v_str.push_back(tmp);
                    tmp.clear();
                }
                old_pos = ++pos;
            }
        }
    }
    void trimTrailingNewlines(std::vector<AdvancedStringContainer> &v_str) {
        std::vector<AdvancedStringContainer> tmp;
        AdvancedStringContainer tmp2;
        AdvancedStringContainer asc_tmp;
        (*this).containerStringSplit(tmp, '\n');
        bool run = true;

        // process vector of sentences (tmp)
        for(int i=0; i < tmp.size(); ++i) {
            AdvancedStringContainer asc = tmp[i];
            if (asc.size()) {
                // process all words, inside a single sentence, in reverse and remove traling white spaces (including words built of white spaces)
                for(int x=asc.size() - 1; x >= 0; x--) {
                    AdvancedString as = asc[x];
                    if(as.size()) {
                        // process a single word in reverse and find all whitespaces
                        for(int y=as.size()-1; y >= 0; y--) {
                            std::string s = as.str();
                            if(s[y] != ' ') {
                                std::string sub = s.substr(0,y);
                                AdvancedString n = AdvancedString(sub, as.fontColor(), as.attributes(), as.bgColor());
                                for(int t = 0; t < x; ++t) {
                                    asc_tmp << asc[t];
                                }
                                asc_tmp << n;
                                v_str.push_back(asc_tmp);
                                run = false;
                                asc_tmp.clear();
                                break;
                            }
                        }
                        if (!run)
                            break;
                    }
                }
                run = true;
            }
        }
    }
//     void subString(std::vector<AdvancedStringContainer> &v_str) {
//
//     }

private:
    std::vector<AdvancedString> sContainer;
};

#endif
