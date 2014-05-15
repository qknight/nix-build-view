#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "Widget.hpp"
class BuildWidget;

class BuildWidgetManager : public Widget {
public:
    static BuildWidgetManager* Instance();
    void add(const char* arg1, const char* arg2);
    int type();
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    unsigned int rowsWantedByWidget();
private:
    BuildWidgetManager();
    std::vector<BuildWidget*> m_builds;
};

#endif // BUILDWIDGETMANAGER_H
