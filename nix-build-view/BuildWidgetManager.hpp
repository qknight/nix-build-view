#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class BuildWidgetManager : public WidgetManagerBase {
public:
    int type();
    static BuildWidgetManager* Instance();
private:
    BuildWidgetManager();
};

#endif // BUILDWIDGETMANAGER_H
