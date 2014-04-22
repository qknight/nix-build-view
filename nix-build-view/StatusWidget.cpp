#include "StatusWidget.hpp"
#include "AdvancedString.hpp"
#include <string>

AdvancedStringContainer StatusWidget::render() {
    AdvancedStringContainer s1;

    AdvancedStringContainer s2;
    std::vector<std::string> el;
    el.push_back(" h help ");
    el.push_back(" 1 combined ");
    el.push_back(" 2 log ");
    el.push_back(" 3 fetching ");
    el.push_back(" 4 building ");

    s2 << "[";
    for (int i=0; i < el.size(); ++i) {
        if (i == m_focus)
            s2 << AdvancedString(el[i], COLOR_WHITE, 0, COLOR_BLUE);
        else
            s2 << el[i];
        if (i != el.size()-1)
            s2 << "|";
    }
    s2 << "]";

    int i = width() - s1.size();
    if (i < 0) i = 0;
    return s2;
}

void StatusWidget::setFocus(int focus) {
    m_focus = focus;
    update();
}
