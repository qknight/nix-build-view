#include "HelpWidget.hpp"

int HelpWidget::type() {
    return WidgetName::HelpWidget;
}

AdvancedStringContainer HelpWidget::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;

    s << AdvancedString("nix-build-view $version (C) 2014++ Joachim Schiele\n", COLOR_CYAN);
    s << AdvancedString("Released under the GNU GPL v3\n", COLOR_CYAN);
    s << "\n";
    s << "         " << "keyboard shortcuts: \n";
    s << "\n";
    s << "         " << AdvancedString("q", COLOR_CYAN) << " - quit the program\n";
    s << "\n";
    s << "         " << AdvancedString("h", COLOR_CYAN) << " - help\n";
    s << "         " << AdvancedString("1", COLOR_CYAN) << " - combined view with log+fetch+build\n";
    s << "         " << AdvancedString("2", COLOR_CYAN) << " - shows the logfile output of nix-build-view\n";
    s << "         " << AdvancedString("3", COLOR_CYAN) << " - shows the download widget (can be scrolled)\n";
    s << "         " << AdvancedString("4", COLOR_CYAN) << " - shows the build widget (can be scrolled)\n";
    s << "\n";
    s << "         " << AdvancedString("up", COLOR_CYAN) << " - scrolls view up\n";
    s << "         " << AdvancedString("down", COLOR_CYAN) << " - scrolls the view down\n";
    s << "         " << AdvancedString("page up", COLOR_CYAN) << " - scrolls view up by several lines\n";
    s << "         " << AdvancedString("page down", COLOR_CYAN) << " - scrolls view down by several lines\n";
    s << "         " << AdvancedString("pos1", COLOR_CYAN) << " - scrolls view to beginning\n";
    s << "         " << AdvancedString("end", COLOR_CYAN) << " - scrolls view to end\n";

//     AdvancedStringContainer out;
//     for(int i=0; i < s.size(); ++i) {
//       int n = s[i].size();
//       out << s[i] << std::string(1,'!');
//     }
    return s;
}
