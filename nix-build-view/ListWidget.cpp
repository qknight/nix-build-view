#include "ListWidget.hpp"

ListWidget::ListWidget() {
    terminal_preprocess();
}

int ListWidget::type() {
    return WidgetName::ListWidget;
}


void ListWidget::splitString(std::vector<std::string> &v_str,const std::string &str,const char ch) {
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

void ListWidget::terminal_preprocess() {
    // - render the text to a buffer
    // - do line-wrapping
    std::string s = m_logfile.str();

    {
        /////// BEGIN: trim end of each string!
        std::stringstream s_tmp;
        std::vector<std::string> tmp;
        splitString(tmp, s, '\n');

        for(int i=0; i < tmp.size(); ++i) {
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
    for (int i=0; i <= s.size(); ++i) {
        if (tmp.size() == width()) {
            m_terminal.push_back(tmp);
            tmp="";
        }

        if (s[i] == '\n')  {
            tmp += std::string(width()-tmp.size(), ' ');
            m_terminal.push_back(tmp);
            tmp="";
            continue;
        }
        tmp += s[i];
    }
}

//FIXME only auto-scroll the view when m_line==0
AdvancedStringContainer ListWidget::render() {
    // - m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

    //copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;

    std::vector<std::string>::const_iterator it_b = m_terminal.begin();
    std::vector<std::string>::const_iterator it_e = m_terminal.end();

    if (it_e - height() - m_line >= it_b)
        it_b = it_e - height() - m_line;

    for(int i=0; i < height(); ++i) {
        if (it_b >= it_e)
            break;
        out << *it_b++;
    }

    return out;
}

void ListWidget::resize(unsigned int w, unsigned int h) {
    Widget::resize(w, h);
    terminal_preprocess();
    update();
}

//FIXME do not recompute the whole buffer every time but instead scan for the last newline and go from there...
void ListWidget::append(std::string line) {
    // replace all \t with '        ' (8 spaces)
    // you can't use copy'n'paste from that terminal, so Makefiles for example will be broken when being copied this way
    std::stringstream buf;

    for(int i=0; i < line.size(); ++i) {
        if (line[i] == '\t')
            buf << "        ";
        else
            buf << line[i];
    }

    // add the new string
    m_logfile << buf.str();
    terminal_preprocess(); //FIXME optimization needed

    update();
}

void ListWidget::keyboardInputHandler(int ch) {
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
        m_line -= 15;
        if (m_line < 0)
            m_line = 0;
        update();
        break;
    default:
        break;
    }
}
