#include "StatusWidget.hpp"

std::string StatusWidget::render(int w, int h) {
    return std::string("nix-build | F1 Help | building: 4/9 | fetching: 3/3 | since 20m30s");
}
