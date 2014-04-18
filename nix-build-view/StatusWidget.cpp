#include "StatusWidget.hpp"
#include <sstream>

AdvancedString StatusWidget::render() {
    std::stringstream s;
    std::string status = std::string("[ h help | 1 combined | 2 log | 3 fetching: 3/3 | 4 building: 4/9 ]");
    int i = width() - status.size();
    if (i < 0) i = 0;
    s << status << " " << std::string(i, ' ');
    return s.str();
}
