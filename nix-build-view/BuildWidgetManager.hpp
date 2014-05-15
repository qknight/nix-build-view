#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class BuildWidgetManager : public WidgetManagerBase {
public:
    int type();
    void add(const char* arg1, const char* arg2);

};

#endif // BUILDWIDGETMANAGER_H
