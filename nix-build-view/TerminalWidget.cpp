#include "TerminalWidget.hpp"

TerminalWidget*
TerminalWidget::Instance()
{
    static TerminalWidget* _instance = new TerminalWidget;
    return _instance;
}

int
TerminalWidget::type() const
{
    return WidgetName::TerminalWidget;
}

AdvancedStringContainer
TerminalWidget::render(unsigned int width, unsigned int height)
{
    // - m_logfile might obviously have more than 28 rows so only 'render' the
    // part we are interested in

    // copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;

    // caches the output for better performance
    if ((m_width != width) || (m_height != height)) {
        m_width     = width;
        m_height    = height;
        AdvancedStringContainer::terminal_rasterize(m_terminal,
                                                    m_logfile,
                                                    this->width());
    }

    std::vector<AdvancedStringContainer>::const_iterator it_b = m_terminal.begin();
    std::vector<AdvancedStringContainer>::const_iterator it_e = m_terminal.end();

    if (it_e - height - m_line >= it_b) {
        it_b = it_e - height - m_line;
    }

    for (unsigned int i = 0; i < height; ++i) {
        if (it_b >= it_e) {
            break;
        }
        AdvancedStringContainer t = *it_b++;
        out << t;
    }

    return out;
}

void
TerminalWidget::append(AdvancedStringContainer line)
{
    // replace all \t with '        ' (8 spaces)
    // you can't use copy'n'paste from that terminal, so Makefiles for example will be broken when being copied this way
    AdvancedStringContainer buf;

    for (unsigned int i = 0; i < line.size(); ++i) {
        AdvancedString a    = line[i];
        std::string s       = a.str();
        std::stringstream ss;

        for (unsigned int x = 0; x < s.size(); ++x) {
            if (s[x] == '\t') {
                ss << "        ";
            } else {
                ss << s[x];
            }
        }
        buf << AdvancedString(ss.str(),
                              a.fontColor(),
                              a.attributes(),
                              a.bgColor());
    }

    // add the new string
    m_logfile << buf;
    std::vector<AdvancedStringContainer> m;
    AdvancedStringContainer::terminal_rasterize(m, buf, this->width());

    for (unsigned int i = 0; i < m.size(); ++i) {
        m_terminal.push_back(m[i]);
    }

    if (m_line != 0) {
        m_line += m.size();
    }

    update();
}

void
TerminalWidget::keyboardInputHandler(int ch)
{
    unsigned int a = 0;

    switch(ch) {
    case(KEY_HOME):
        m_line = m_terminal.size() - height();
        update();
        break;

    case(KEY_END):
        m_line = 0;
        update();
        break;

    case(KEY_UP):
        m_line += 1;
        if (m_line > m_terminal.size() - height()) {
            m_line = m_terminal.size() - height();
        }
        update();
        break;

    case(KEY_DOWN):
        if (m_line > 0) {
            m_line -= 1;
        }
        update();
        break;

    case(KEY_PPAGE):
        m_line += 15;
        if (m_line > m_terminal.size() - height()) {
            m_line = m_terminal.size() - height();
        }
        update();
        break;

    case(KEY_NPAGE):
        a = m_line;
        m_line -= 15;
        if (m_line > a) {
            m_line = 0;
        }
        update();
        break;

    default:
        break;

    }
}

