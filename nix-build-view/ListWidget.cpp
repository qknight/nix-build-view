#include "ListWidget.hpp"

std::string ListWidget::render(int w, int h) {
    // FIXME
    // 2. count all \n newlines and render the text to a buffer
    // 3. do line-wrapping
    // 4. m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

    std::string s = m_logfile.str();
    std::vector<std::string> terminal;

    //render the m_logfile into a terminal with width w
    std::string tmp;
    for (int i=0; i <= s.size(); ++i) {
        if (s[i] == '\n' || tmp.size() == w-1) {
            terminal.push_back(tmp);
            tmp="";
        } else {
            tmp += s[i];
        }
    }

    //copy the last h elements from terminal to the out buffer
    std::stringstream out;
    
    std::vector<std::string>::const_iterator it_b = terminal.begin();
    std::vector<std::string>::const_iterator it_e = terminal.end();
    
    if (it_e - h >= it_b)
      it_b = it_e - h;
    
    for(; it_b != it_e; it_b++) {
        out << *it_b << std::endl;
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
