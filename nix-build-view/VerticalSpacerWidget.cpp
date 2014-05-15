#include "VerticalSpacerWidget.hpp"

unsigned int VerticalSpacerWidget::rowsWantedByWidget() {
  return 0; 
}

int VerticalSpacerWidget::type() {
    return WidgetName::VerticalSpacerWidget;
}

AdvancedStringContainer VerticalSpacerWidget::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer a;
//     a << "hello world";
    return a;
}
