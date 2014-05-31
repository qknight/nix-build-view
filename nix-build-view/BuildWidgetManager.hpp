#ifndef BUILDWIDGETMANAGER_H
#define BUILDWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class BuildWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static BuildWidgetManager* Instance();
    void addBuild(std::string UUID, std::vector< std::string > phases);
    void removeBuild(std::string UUID);
    int getPhase(std::string UUID);
    void setPhase(std::string UUID, int phase);
private:
    BuildWidgetManager();
    void sort();
};

#endif // BUILDWIDGETMANAGER_H
