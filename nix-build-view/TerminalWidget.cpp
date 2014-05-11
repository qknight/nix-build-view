#include "TerminalWidget.hpp"

TerminalWidget::TerminalWidget() {
    terminal_rasterize();
}

int TerminalWidget::type() {
    return WidgetName::TerminalWidget;
}

void TerminalWidget::splitString(std::vector<std::string> &v_str,const std::string &str,const char ch) {
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
        v_str.push_back(sub);
        old_pos = ++pos;
    }
}

//FIXME this ignores ncurses coloring implemented in AdvancedString and AdvancedStringContainer!!!
void TerminalWidget::terminal_rasterize() {
    // - render the text to a buffer
    // - do line-wrapping
    std::string s = m_logfile.str();

    {
        /////// BEGIN: trim end of each string!
        std::stringstream s_tmp;
        std::vector<std::string> tmp;
        splitString(tmp, s, '\n');

        for(unsigned int i=0; i < tmp.size(); ++i) {
            std::string::const_iterator it_b = tmp[i].begin();
            std::string::const_iterator it_e = tmp[i].end();
            std::string::const_iterator it_tmp = it_e-1;

            while(it_tmp < it_e && it_tmp >= it_b) {
                if (*it_tmp == ' ') {
                    --it_tmp;
                } else {
                    s_tmp << std::string(it_b, it_tmp+1);
                    break;
                }
            }
            if(i < tmp.size()-1)
                s_tmp << std::endl;
        }
        /////// END: trim end of each string!
        s = s_tmp.str();
    }


    //render the m_logfile into a terminal with width w
    m_terminal.clear();
    std::string tmp;
    for (unsigned int i=0; i <= s.size(); ++i) {
        if (tmp.size() == width()) {
            m_terminal.push_back(tmp);
            tmp="";
        }

        if (s[i] == '\n')  {
            tmp += std::string(width()-tmp.size(), '?');
            m_terminal.push_back(tmp);
            tmp="";
            continue;
        }
        tmp += s[i];
    }
}

//FIXME only auto-scroll the view when m_line==0
AdvancedStringContainer TerminalWidget::render(unsigned int width, unsigned int height) {
    // - m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

    //copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;
    AdvancedStringContainer d;

    if ((m_width != width) || (m_height != height)) {
        m_width = width;
        m_height = height;
        terminal_rasterize();
    }

    std::vector<std::string>::const_iterator it_b = m_terminal.begin();
    std::vector<std::string>::const_iterator it_e = m_terminal.end();

    if (it_e - height - m_line >= it_b)
        it_b = it_e - height - m_line;

    for(unsigned int i=0; i < height; ++i) {
        if (it_b >= it_e)
            break;
        out << *it_b++;
    }
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiVVVVVVVVVVVVVVVVVVVVVVVVVV4444444444444444444444444499999999999999999999a";
//     d << *m_terminal.begin();
//     d << *m_terminal.begin();
//     d << (float) height;
//     return d;

    return out;
}

//FIXME do not recompute the whole buffer every time but instead scan for the last newline and go from there...
void TerminalWidget::append(AdvancedStringContainer line) {
    // replace all \t with '        ' (8 spaces)
    // you can't use copy'n'paste from that terminal, so Makefiles for example will be broken when being copied this way
    AdvancedStringContainer buf;

    //FIXME broken
//     for(int i=0; i < line.size(); ++i) {
//         if (line[i] == '\t')
//             buf << "        ";
//         else
//             buf << line[i];
//     }
    //FIXME filter for \t is not included right now!
//     buf << "FIXME filter for '\\t' is not included right now!\n";
    buf << line;

    // add the new string
    m_logfile << buf;
    terminal_rasterize();

    update();
}

void TerminalWidget::keyboardInputHandler(int ch) {
    unsigned int a=0;
    switch(ch) {
    case(KEY_HOME):
        m_line = m_terminal.size()-height();
        update();
        break;
    case(KEY_END):
        m_line = 0;
        update();
        break;
    case(KEY_UP):
        m_line += 1;
        if (m_line > m_terminal.size()-height())
            m_line = m_terminal.size()-height();
        update();
        break;
    case(KEY_DOWN):
        if (m_line > 0)
            m_line -= 1;
        update();
        break;
    case(KEY_PPAGE):
        m_line += 15;
        if (m_line > m_terminal.size()-height())
            m_line = m_terminal.size()-height();
        update();
        break;
    case(KEY_NPAGE):
        a = m_line;
        m_line -= 15;
        if (m_line > a)
            m_line = 0;
        update();
        break;
    default:
        break;
    }
}

