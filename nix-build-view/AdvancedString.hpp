#ifndef ADVANCEDSTRING_HPP
#define ADVANCEDSTRING_HPP

#include "ncurses.h"
#include "ColorCodes.h"
#include <string>

/*
 * to get an idea what this is all about have a look at the unit test which illustrates the concepts with lots of examples
 */
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
    std::string terminalString() {
        std::stringstream ss;
        std::string color;
        switch (m_fontColor) {
        case COLOR_BLACK:
            color= "\033[30m";
            break;
        case COLOR_RED:
            color= "\033[31m";
            break;
        case COLOR_GREEN:
            color= "\033[32m";
            break;
        case COLOR_YELLOW:
            color= "\033[33m";
            break;
        case COLOR_BLUE:
            color= "\033[34m";
            break;
        case COLOR_MAGENTA:
            color= "\033[35m";
            break;
        case COLOR_CYAN:
            color= "\033[36m";
            break;
        case COLOR_WHITE:
            color= "\033[37m";
            break;
        }
        ss << color << m_str << RESET;
        return ss.str();
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

    /*
     * like std::string.substr this function builds a substring starting at b and ending at e
     *  - if b > e, an empty AdvancedStringContainer is returned
     *  - if b or e is outside in, then an empty AdvancedStringContainer is returned
     *  - if [ 0 <= b < e <= in.str_size ], then it will return a AdvancedStringContainer with at least one element in it
     *
     * WARNING: it is assumed that the string is free of \n or \t chars!
     */
    //FIXME implement this and write unit tests for it, finally make us of it in the render() function to limit the string!
    static void substr(std::vector<AdvancedStringContainer> &out,  AdvancedStringContainer  &in , unsigned int b, unsigned int e) {
//         AdvancedStringContainer tmp;
//         for (unsigned int i=0; i < in.size(); i++) {
//             AdvancedString as = in[i];
//             std::string str = as.str();
//             std::string sub;
//             std::string::size_type pos = 0;
//             std::string::size_type old_pos = 0;
//             bool flag=true;
//
//             while(flag) {
//                 pos=str.find_first_of(ch,pos);
//                 if(pos == std::string::npos)
//                 {
//                     flag = false;
//                     pos = str.size();
//                 }
//                 sub = str.substr(old_pos, pos-old_pos);
//                 tmp << AdvancedString(sub, as.fontColor(), as.attributes(), as.bgColor());
//                 if (flag || i == in.size()-1) {
//                     out.push_back(tmp);
//                     tmp.clear();
//                 }
//                 old_pos = ++pos;
//             }
//         }
    }

    /*
     * removes newline characters by transforming a AdvancedStringContainer (a list of words) into vector<AdvancedStringContainer> (a vector of sentences)
     */
    static void containerStringSplit(std::vector<AdvancedStringContainer> &out,  AdvancedStringContainer  &in , const char ch) {
        AdvancedStringContainer tmp;
        for (unsigned int i=0; i < in.size(); i++) {
            AdvancedString as = in[i];
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
                sub = str.substr(old_pos, pos-old_pos);
                tmp << AdvancedString(sub, as.fontColor(), as.attributes(), as.bgColor());
                if (flag || i == in.size()-1) {
                    out.push_back(tmp);
                    tmp.clear();
                }
                old_pos = ++pos;
            }
        }
    }

    /*
     * trimes right side of a sentence (AdvancedStringContainer are considered sentences) and removes newline characters using containerStringSplit
     */
    static void trimEndAndRemoveNewlineChars(std::vector<AdvancedStringContainer> &out,  AdvancedStringContainer  &in) {
        std::vector<AdvancedStringContainer> tmp;
        AdvancedStringContainer tmp2;
        AdvancedStringContainer asc_tmp;
        containerStringSplit(tmp, in, '\n');

        bool run = true;

        // process vector of sentences (tmp)
        for(unsigned int i=0; i < tmp.size(); ++i) {
            AdvancedStringContainer asc = tmp[i];
            if (asc.str_size()) {
                // process all words, inside a single sentence, in reverse and remove traling white spaces (including words built of white spaces)
                for(int x=asc.size() - 1; x >= 0; x--) {
                    AdvancedString as = asc[x];
                    if(as.size()) {
                        // process a single word in reverse and find all whitespaces
                        std::string s = as.str();
                        for(int y=as.size()-1; y >= 0; y--) {
                            if(s[y] != ' ') {
                                std::string sub = s.substr(0,y+1);
                                AdvancedString n = AdvancedString(sub, as.fontColor(), as.attributes(), as.bgColor());
                                for(int t = 0; t < x; ++t) {
                                    asc_tmp << asc[t];
                                }
                                asc_tmp << n;
                                out.push_back(asc_tmp);
                                run = false;
                                asc_tmp.clear();
                                break;
                            }

                        }

                        if (!run) {
                            run = true;
                            break;
                        }
                    }
                    if (x == 0) {
                        AdvancedString n = AdvancedString("", COLOR_YELLOW, as.attributes(), as.bgColor());
                        asc_tmp << n;
                        out.push_back(asc_tmp);
                        asc_tmp.clear();
                    }
                }
            } else {		//p hinzu

                AdvancedString n = AdvancedString("", COLOR_YELLOW);
                asc_tmp << n;
                out.push_back(asc_tmp);
                asc_tmp.clear();
            }
        }
    }
    /*
     * translates AdvancedStringContainer (a list of words) into a fixed width vector of AdvancedStringContainer for later displaying
     * - each vector element holds exactly width chars
     * - if the input doesn't fill the whole line it is padded with white spaces
     *
     * this function is used by the Widget::render() call to compute the width x height chars needed for filling the widget space on the terminal
     */
    static void terminal_rasterize(std::vector<AdvancedStringContainer> &out, AdvancedStringContainer &in, int width) {
        // - render the text to a buffer4
        // - do line-wrapping
        std::vector<AdvancedStringContainer> buf;

        // trims trailing newlines and writes result to buf
        trimEndAndRemoveNewlineChars(buf, in);

        // render the m_logfile into a terminal with width()
        out.clear();

        AdvancedStringContainer tmp;
        // process vector of sentences (buf)
        for(unsigned int i=0; i < buf.size(); ++i) {
            AdvancedStringContainer asc = buf[i];
            // process all words, inside a single sentence,
            for(unsigned int x=0; x < asc.size(); x++) {
                AdvancedString as = asc[x];
                AdvancedString atmp;

//                 std::string::iterator it_begin = as.str().begin();
//                 std::string::iterator it_p = as.str().begin();
//                 std::string::iterator it_e = as.str().end();

                if ((as.size() == 0) && (x == asc.size()-1) && (i != buf.size()-1)) {
                    tmp << AdvancedString(std::string(width, ' '), COLOR_BLUE);
                    out.push_back(tmp);
                    tmp.clear();
                }

                while(as.size()) {
                    int size = 0;
                    if (as.size() > width-tmp.str_size()) // if string is bigger than available size
                        size = width-tmp.str_size();
                    else
                        size = as.size();
                    std::string sub1 = as.str().substr(0, size);
                    atmp = AdvancedString(sub1, as.fontColor(), as.attributes(), as.bgColor());
                    std::string sub2 = as.str().substr(size, as.size()-size);
                    as = AdvancedString(sub2, as.fontColor(), as.attributes(), as.bgColor());
                    tmp << atmp;
                    // check if padding is needed
                    if ((width-tmp.str_size() == 0) || (x == asc.size()-1)) {
                        int f = width-tmp.str_size();
                        if (f > 0) {
                            tmp << AdvancedString(std::string(f, ' '));
                        }
                        out.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
        }
    }

private:
    std::vector<AdvancedString> sContainer;
};

#endif







