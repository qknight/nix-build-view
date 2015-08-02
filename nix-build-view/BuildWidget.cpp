#include "BuildWidget.hpp"
#include <sstream>

BuildWidget::BuildWidget(std::string name,
                         std::vector< std::string > phases)
{
    m_name = name;
    m_phases = phases;
    m_currentPhase = 0;
}

int
BuildWidget::type() const
{
    return WidgetName::BuildWidget;
}

AdvancedStringContainer
BuildWidget::render(unsigned int width,
                    unsigned int height)
{
    AdvancedStringContainer s;
    //FIXME if width is very small, kick the m_name beginning from the left

    if (m_currentPhase < m_phases.size()) {
        int i = width - m_name.size() - m_phases[m_currentPhase].size() - 2;

        if (i < 0) {
            i = 0;
        }
        s << AdvancedString(m_name, COLOR_MAGENTA)
          << " "
          << std::string(i, '.')
          << " "
          << AdvancedString(m_phases[m_currentPhase], COLOR_YELLOW);
    }

    return s;
}
