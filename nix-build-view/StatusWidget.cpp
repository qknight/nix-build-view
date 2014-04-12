#include "StatusWidget.hpp"

std::string StatusWidget::render(int w, int h) {
    return std::string("[ h help | 1 combined | 2 log | 3 fetch | 4 build ] - building: 4/9 | fetching: 3/3 | since 20m30s");
}
