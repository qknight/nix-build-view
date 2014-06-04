#include "StatusWidget.hpp"
#include "AdvancedString.hpp"
#include <string>

int StatusWidget::type() const {
    return WidgetName::StatusWidget;
}

AdvancedStringContainer StatusWidget::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s1;

    AdvancedStringContainer s2;
    std::vector<std::string> el;
    el.push_back(" h help ");
    el.push_back(" 1 combined ");
    el.push_back(" 2 log ");
    el.push_back(" 3 fetching ");
    el.push_back(" 4 building ");

    s2 << "[";
    for (unsigned int i=0; i < el.size(); ++i) {
        if (i == m_focus)
            s2 << AdvancedString(el[i], COLOR_WHITE, 0, COLOR_BLUE);
        else
            s2 << el[i];
        if (i != el.size()-1)
            s2 << "|";
    }
    s2 << "]";

    if (m_fetches) {
        s2 << " " << AdvancedString(std::to_string(m_fetches), COLOR_GREEN);
        if (m_fetches == 1)
            s2 << AdvancedString(" fetch", COLOR_GREEN);
        else
            s2 << AdvancedString(" fetches", COLOR_GREEN);
    }

    if (m_builds) {
        s2 << " " << AdvancedString(std::to_string(m_builds), COLOR_MAGENTA);
        if (m_builds == 1)
            s2 << AdvancedString(" build", COLOR_MAGENTA);
        else
            s2 << AdvancedString(" builds", COLOR_MAGENTA);
    }

    int i = width - s1.size();
    if (i < 0) i = 0;
    return s2;
}

void StatusWidget::setFocus(int focus) {
    m_focus = focus;
    update();
}

StatusWidget* StatusWidget::Instance() {
    static StatusWidget* _instance = new StatusWidget;
    return _instance;
}

StatusWidget::StatusWidget()
{

}

void StatusWidget::setBuilds(unsigned int builds) {
    m_builds=builds;
    update();
}

void StatusWidget::setFetches(unsigned int fetches) {
    m_fetches=fetches;
    update();
}
