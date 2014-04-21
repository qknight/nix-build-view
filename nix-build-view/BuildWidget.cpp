#include "BuildWidget.hpp"
#include <sstream>

BuildWidget::BuildWidget(std::string name, std::string status) {
    m_name = name;
    m_status = status;
}


AdvancedStringContainer BuildWidget::render() {
    AdvancedStringContainer s;
    int i = width() - m_name.size() - m_status.size() - 2;
    if (i < 0) i = 0;
    s << AdvancedString(m_name, COLOR_MAGENTA) << " " << std::string(i, '.') << " " << AdvancedString(m_status, COLOR_YELLOW);
    return s;
}
