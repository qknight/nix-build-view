#include "TerminalWidget.hpp"

TerminalWidget* TerminalWidget::Instance() {
    static TerminalWidget* _instance = new TerminalWidget;
    return _instance;
}

int TerminalWidget::type() {
    return WidgetName::TerminalWidget;
}

// translates the m_logfile into a fixed width vector for later displaying
void TerminalWidget::terminal_rasterize(std::vector<AdvancedStringContainer> &terminal, int width) {
    // - render the text to a buffer
    // - do line-wrapping
    std::vector<AdvancedStringContainer> buf;

    // trims trailing newlines and writes result to buf
    m_logfile.trimTrailingNewlines(buf);

    // render the m_logfile into a terminal with width()
    terminal.clear();

    AdvancedStringContainer tmp;
    // process vector of sentences (buf)
    //FIXME there is still some bugs in here but it works 90% ;-)
    for(int i=0; i < buf.size(); ++i) {
        AdvancedStringContainer asc = buf[i];
        // process all words, inside a single sentence,
        for(int x=0; x < asc.size(); x++) {
            AdvancedString as = asc[x];

            std::string::iterator it_b = as.str().begin();
            std::string::iterator it_e = as.str().end();

            while(true) {
                AdvancedString atmp;
                int size = 0;
                if (width-tmp.str_size() < it_e - it_b) {
                    if (it_e - it_b > width-tmp.str_size()) // if string is bigger than available size
                        size = width-tmp.str_size();
                    else
                        size = it_e - it_b;
                    //FIXME begin isn't always correct
//                     std::string reset = as.str().substr(it_b - as.str().begin(), size);
                    std::string reset = as.str().substr(0, size);
                    atmp = AdvancedString(reset, as.fontColor(), as.attributes(), as.bgColor());
                } else {
                    atmp = as;
                }
                tmp << atmp;
                it_b += size;
                // check if padding is needed
                if ((width-tmp.str_size() == 0) || (x == asc.size()-1)) {
                    int f = width-tmp.str_size();
                    if (f > 0) {
                        f-=1;
                        tmp << AdvancedString(std::string(f, '?'), COLOR_BLUE);
			tmp << AdvancedString("!", COLOR_RED);
                    }
                    terminal.push_back(tmp);
                    tmp.clear();
                }
                break;//FIXME find the condition we need to break which should be that all parts of as were consumed into tmp
            }
        }
    }
}

//FIXME only auto-scroll the view when m_line==0
AdvancedStringContainer TerminalWidget::render(unsigned int width, unsigned int height) {
    // - m_logfile might obviously have more than 28 rows so only 'render' the part we are interested in

    //copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;

    //caches the output for better performance
    if ((m_width != width) || (m_height != height)) {
        m_width = width;
        m_height = height;
        terminal_rasterize(m_terminal, this->width());
    }

    std::vector<AdvancedStringContainer>::const_iterator it_b = m_terminal.begin();
    std::vector<AdvancedStringContainer>::const_iterator it_e = m_terminal.end();

    if (it_e - height - m_line >= it_b)
        it_b = it_e - height - m_line;

    for(unsigned int i=0; i < height; ++i) {
        if (it_b >= it_e)
            break;
        AdvancedStringContainer t = *it_b++;
        out << t;
    }

    return out;
}

void TerminalWidget::append(AdvancedStringContainer line) {
    // replace all \t with '        ' (8 spaces)
    // you can't use copy'n'paste from that terminal, so Makefiles for example will be broken when being copied this way
    AdvancedStringContainer buf;

    for(int i=0; i < line.size(); ++i) {
        AdvancedString a = line[i];
        std::string s = a.str();
        std::stringstream ss;

        //FIXME could be implemented more efficiently
        for(int x=0; x < s.size(); ++x) {
            if (s[x] == '\t')
                ss << "        ";
            else
                ss << s[x];
        }
        buf << AdvancedString(ss.str(), a.fontColor(), a.attributes(), a.bgColor());
    }

    // add the new string
    m_logfile << buf;
    terminal_rasterize(m_terminal, width());

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



