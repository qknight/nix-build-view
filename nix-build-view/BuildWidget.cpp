#include "BuildWidget.hpp"

BuildWidget::BuildWidget(std::string name) {
  m_name = name;
}


std::string BuildWidget::render() {
  return m_name;
}
