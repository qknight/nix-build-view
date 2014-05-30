#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class BuildWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static BuildWidgetManager* Instance();
    void addBuild(std::string UUID, std::string bar);
private:
    BuildWidgetManager();
    void sort();
};

#endif // BUILDWIDGETMANAGER_H
