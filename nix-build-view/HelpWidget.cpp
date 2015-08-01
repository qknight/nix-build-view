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

      << "\n"
      << "\n"
      << "     " << "keyboard shortcuts: \n"
      << "\n"
      << "         " << AdvancedString(p("q"), COLOR_CYAN, WA_BOLD)
      << " - quit the program\n"

      << "\n"
      << "         " << AdvancedString(p("h"), COLOR_CYAN, WA_BOLD)
      << " - help\n"

      << "         " << AdvancedString(p("1"), COLOR_CYAN, WA_BOLD)
      << " - combined view with log+fetch+build\n"

      << "         " << AdvancedString(p("2"), COLOR_CYAN, WA_BOLD)
      << " - shows the logfile output of nix-build-view\n"

      << "         " << AdvancedString(p("3"), COLOR_CYAN, WA_BOLD)
      << " - shows the download widget (can be scrolled)\n"

      << "         " << AdvancedString(p("4"), COLOR_CYAN, WA_BOLD)
      << " - shows the build widget (can be scrolled)\n"

      << "\n"
      << "     " << "using the views: \n"
      << "\n"
      << "         " << AdvancedString(p("up"), COLOR_CYAN, WA_BOLD)
      << " - scrolls view up\n"

      << "         " << AdvancedString(p("down"), COLOR_CYAN, WA_BOLD)
      << " - scrolls the view down\n"

      << "         " << AdvancedString(p("page up"), COLOR_CYAN, WA_BOLD)
      << " - scrolls view up by several lines\n"

      << "         " << AdvancedString(p("page down"), COLOR_CYAN, WA_BOLD)
      << " - scrolls view down by several lines\n"

      << "         " << AdvancedString(p("pos1"), COLOR_CYAN, WA_BOLD)
      << " - scrolls view to beginning\n"

      << "         " << AdvancedString(p("end"), COLOR_CYAN, WA_BOLD)
      << " - scrolls view to end\n"

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

