#include "BuildWidgetManager.hpp"

BuildWidgetManager::BuildWidgetManager() {
}

int BuildWidgetManager::type() const {
    return WidgetName::BuildWidgetManager;
}

BuildWidgetManager* BuildWidgetManager::Instance() {
    static BuildWidgetManager* _instance = new BuildWidgetManager;
    return _instance;
}

void BuildWidgetManager::sort() {

}
