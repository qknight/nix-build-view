#include "HelpWidget.hpp"

int HelpWidget::type() {
    return WidgetName::HelpWidget;
}


AdvancedStringContainer HelpWidget::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
    s << "\
         .                                                   "\
      "        ,                                                   \n"\
      "    `   ,                                                   \n"\
      "    .,` ,  .,                                               \n"\
      "      ,,,  .,        :;     ;,  @            `#@+      `@@' \n"\
      ",;.   `;,, ., ;;     +@#    @:  @           @@':@@+   #@';@`\n"\
      "  ;; ;;  `,,:;.      +@@`   @:             @@    `@:  @     \n"\
      "   :;`     ,;        +@#@   @:  +  +`   +. @      @@  @     \n"\
      " .;,,      .,        +@ @#  @:  @  '@  @@ ;@      `@  @@.   \n"\
      ";;  ,      .,  ,     +@ .@  @:  @   @@,@  +@       @   #@@: \n"\
      "    ,      .,,,      +@  @@ @:  @    @@   '@       @     ;@'\n"\
      "    ,`     ,,`       +@   @;@:  @    @@   `@      '@      '@\n"\
      "  ,,,;;  `,.`,`      +@   :@@:  @   @#+@   @@     @+      ;@\n"\
      "`,` , `;;,    ,,     +@    @@:  @  ;@  @@   @@  `@@   '  .@'\n"\
      "    ,   ;;.          +@     @:  @  @`   @.   @@@@;    @@@@; \n"\
      "    ,   ; ;;                                                \n"\
      "    .   ;                                                   \n"\
      "        ;                                                   \n"\
      "        :                                             ";
    return s;
}
