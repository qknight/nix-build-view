#include "HelpWidget.hpp"

int HelpWidget::type() {
    return WidgetName::HelpWidget;
}


AdvancedStringContainer HelpWidget::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
//     s << "\
//          .                                                   "\
//       "        ,                                                   \n"\
//       "    `   ,                                                   \n"\
//       "    .,` ,  .,                                               \n"\
//       "      ,,,  .,        :;     ;,  @            `#@+      `@@' \n"\
//       ",;.   `;,, ., ;;     +@#    @:  @           @@':@@+   #@';@`\n"\
//       "  ;; ;;  `,,:;.      +@@`   @:             @@    `@:  @     \n"\
//       "   :;`     ,;        +@#@   @:  +  +`   +. @      @@  @     \n"\
//       " .;,,      .,        +@ @#  @:  @  '@  @@ ;@      `@  @@.   \n"\
//       ";;  ,      .,  ,     +@ .@  @:  @   @@,@  +@       @   #@@: \n"\
//       "    ,      .,,,      +@  @@ @:  @    @@   '@       @     ;@'\n"\
//       "    ,`     ,,`       +@   @;@:  @    @@   `@      '@      '@\n"\
//       "  ,,,;;  `,.`,`      +@   :@@:  @   @#+@   @@     @+      ;@\n"\
//       "`,` , `;;,    ,,     +@    @@:  @  ;@  @@   @@  `@@   '  .@'\n"\
//       "    ,   ;;.          +@     @:  @  @`   @.   @@@@;    @@@@; \n"\
//       "    ,   ; ;;                                                \n"\
//       "    .   ;                                                   \n"\
//       "        ;                                                   \n"\
//       "        :                                             ";
    
    s << "         " << "keyboard shortcuts: \n\n";
    s << "         " << AdvancedString("up", COLOR_CYAN) << " - scrolls view up\n";
    s << "         " << AdvancedString("down", COLOR_CYAN) << " - scrolls the view down\n";
    s << "         " << AdvancedString("page up", COLOR_CYAN) << " - scrolls view up by several lines\n";
    s << "         " << AdvancedString("page down", COLOR_CYAN) << " - scrolls view down by several lines\n";
    s << "         " << AdvancedString("h", COLOR_CYAN) << " - help\n";
    s << "         " << AdvancedString("1", COLOR_CYAN) << " - combined view with log+fetch+build\n";
    s << "         " << AdvancedString("2", COLOR_CYAN) << " - shows the logfile output of nix-build-view\n";
    s << "         " << AdvancedString("3", COLOR_CYAN) << " - shows the download widget (can be scrolled)\n";
    s << "         " << AdvancedString("4", COLOR_CYAN) << " - shows the build widget (can be scrolled)\n";
    
    
    
    return s;
}
