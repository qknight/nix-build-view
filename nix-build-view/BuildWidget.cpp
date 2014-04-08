#include "BuildWidget.hpp"

BuildWidget::BuildWidget(std::string name) {
  m_name = name;
}


std::string BuildWidget::render(int w, int h) {
  return m_name;
}
