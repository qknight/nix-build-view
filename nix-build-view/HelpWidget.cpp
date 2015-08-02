#include "HelpWidget.hpp"
#include "WindowManager.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>

int
HelpWidget::type() const
{
    return WidgetName::HelpWidget;
}

std::string
HelpWidget::p(std::string s)
{
    std::stringstream ss;
    ss << std::setw(10) << std::left << s;

    return ss.str();
}

AdvancedStringContainer
HelpWidget::render(unsigned int width, unsigned int height)
{
    //copy the last h elements from terminal to the out buffer
    AdvancedStringContainer out;
    AdvancedStringContainer s;

    s << AdvancedString("nix-build-view ", COLOR_CYAN, WA_BOLD)
      << AdvancedString(WindowManager::Instance()->version(), COLOR_CYAN)
      << AdvancedString(" (c) 2014++ Joachim Schiele\n", COLOR_CYAN, WA_BOLD)

      << AdvancedString("Released under the GNU GPL v3\n", COLOR_CYAN, WA_BOLD)

#define __as(txt) AdvancedString((txt), COLOR_CYAN, WA_BOLD)
      << "\n"
      << "\n"
      << "     " << "keyboard shortcuts: \n"
      << "\n"
      << "         " << __as(p("q"))
      << " - quit the program\n"

      << "\n"
      << "         " << __as(p("h"))
      << " - help\n"

      << "         " << __as(p("1"))
      << " - combined view with log+fetch+build\n"

      << "         " << __as(p("2"))
      << " - shows the logfile output of nix-build-view\n"

      << "         " << __as(p("3"))
      << " - shows the download widget (can be scrolled)\n"

      << "         " << __as(p("4"))
      << " - shows the build widget (can be scrolled)\n"

      << "\n"
      << "     " << "using the views: \n"
      << "\n"
      << "         " << __as(p("up"))
      << " - scrolls view up\n"

      << "         " << __as(p("down"))
      << " - scrolls the view down\n"

      << "         " << __as(p("page up"))
      << " - scrolls view up by several lines\n"

      << "         " << __as(p("page down"))
      << " - scrolls view down by several lines\n"

      << "         " << __as(p("pos1"))
      << " - scrolls view to beginning\n"

      << "         " << __as(p("end"))
      << " - scrolls view to end\n"
#undef __as

      << "\n"
      << "         "
      << "note: if you scroll to the end of the log (2) 'auto-scroll' will be active\n";


    //caches the output for better performance
    if ((m_width != width) || (m_height != height)) {
        m_width  = width;
        m_height = height;
        AdvancedStringContainer::terminal_rasterize(m_terminal, s, width);
    }

    std::vector<AdvancedStringContainer>::const_iterator it_b = m_terminal.begin();
    std::vector<AdvancedStringContainer>::const_iterator it_e = m_terminal.end();

    int m_line = 0;

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

