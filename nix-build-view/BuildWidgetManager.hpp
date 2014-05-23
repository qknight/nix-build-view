#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class BuildWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static BuildWidgetManager* Instance();
private:
    BuildWidgetManager();
    void sort();
};

#endif // BUILDWIDGETMANAGER_H
