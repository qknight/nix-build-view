#ifndef BUILDWIDGET__HPP
#define BUILDWIDGET__HPP

#include "Widget.hpp"
#include <string>

class BuildWidget : public Widget {
    friend class BuildWidgetManager;
public:
    BuildWidget(std::string name, std::vector<std::string> phases);
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    int type() const;
    int getPhase() const { return m_currentPhase; } ;
protected:
    std::string m_name;
    std::vector<std::string> m_phases;
    int m_currentPhase;
};

#endif
