#include "BuildWidget.hpp"
#include <sstream>

BuildWidget::BuildWidget(std::string name, std::string status) {
    m_name = name;
    m_status = status;
}


std::string BuildWidget::render() {
    std::stringstream s;
    int i = width() - m_name.size() - m_status.size() - 2;
    if (i < 0) i = 0;
    s << m_name << " " << std::string(i, '.') << " " << m_status;
    return s.str();
}
