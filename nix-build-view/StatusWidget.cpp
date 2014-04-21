#include "StatusWidget.hpp"
#include "AdvancedString.hpp"
#include <string>

AdvancedStringContainer StatusWidget::render() {
    AdvancedStringContainer s1;
    
    AdvancedStringContainer s2;
    s2 << "[ h help |" << AdvancedString(std::string(" 1 combined "), COLOR_WHITE, 0, COLOR_BLUE) << "| 2 log | 3 fetching: 3/3 | 4 building: 4/9 ]";
    int i = width() - s1.size();
    if (i < 0) i = 0;
//     s2 << s1 << " " << std::string(i, ' ');
    return s2;
}
