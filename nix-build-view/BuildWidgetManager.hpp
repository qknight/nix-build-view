#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "Widget.hpp"

class BuildWidgetManager : public Widget {
public:
    static BuildWidgetManager* Instance();
    int type();
    AdvancedStringContainer render(unsigned int width, unsigned int height);
private:
    BuildWidgetManager();
};

#endif // BUILDWIDGETMANAGER_H
