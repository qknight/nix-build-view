#include "ListWidget.hpp"

void ListWidget::splitString(std::vector<std::string> &v_str,const std::string &str,const char ch) {
    std::string sub;
    std::string::size_type pos = 0;
    std::string::size_type old_pos = 0;
    bool flag=true;
     
    while(flag)
    {
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

//FIXME buffer the result, only compute this stuff when the terminal width changes
std::string ListWidget::render(int w, int h) {
    // - render the text to a buffer
    // - do line-wrapping
    // - m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

    std::string s = m_logfile.str();
    std::stringstream s_tmp;
    std::vector<std::string> terminal;

    {
      //FIXME this algorithm has a bug i can't find!
        /////// BEGIN: trim end of each string!
        std::string::const_iterator it_b = s.begin();

        std::string::const_iterator it_tmp = it_b;
        std::string::const_iterator it_tmp2 = it_b;
        std::string::const_iterator it_tmp3 = it_b;

        while(it_tmp < s.end()) {
            if (*it_tmp == '\n') {
                it_tmp2 = it_tmp-1;
                while(it_tmp2 > it_b) {
                    if (*it_tmp2 == ' ') {
                        --it_tmp2;
                    } else {
                        s_tmp << std::string(it_b, it_tmp2);
                        it_b = it_tmp++;
                        break;
                    }
                }
                s_tmp << "newline" << std::endl;
            }
//             if (*it_tmp == ' ')
//               it_b = it_tmp;
            
            it_tmp++;
        }
        s = s_tmp.str();
        /////// END: trim end of each string!
    }

    //render the m_logfile into a terminal with width w
    std::string tmp;
    for (int i=0; i <= s.size(); ++i) {
        if (tmp.size() == w) {
            terminal.push_back(tmp);
            tmp="";
        }
        if (s[i] == '\n')  {
            if(tmp != "") {
                //fill each incomplete line with whitespaces so that \n isn't needed
                tmp += std::string(w-tmp.size(), ' ');
                terminal.push_back(tmp);
            }
            tmp="";
            continue;
        }

        tmp += s[i];
    }

    //copy the last h elements from terminal to the out buffer
    std::stringstream out;

    std::vector<std::string>::const_iterator it_b = terminal.begin();
    std::vector<std::string>::const_iterator it_e = terminal.end();

    if (it_e - h >= it_b)
        it_b = it_e - h;

    for(; it_b != it_e; it_b++) {
        out << *it_b;
    }
    return out.str();
}

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

    m_logfile << buf.str();
}
