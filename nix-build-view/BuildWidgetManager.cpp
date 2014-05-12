#include "BuildWidgetManager.hpp"
AdvancedStringContainer BuildWidgetManager::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
    s << "BuildWidgetManager hello world";
    return s;
}

int BuildWidgetManager::type() {
    return WidgetName::BuildWidgetManager;
}

BuildWidgetManager* BuildWidgetManager::Instance() {
    static BuildWidgetManager* _instance = new BuildWidgetManager;
    return _instance;
}

BuildWidgetManager::BuildWidgetManager()
{

}
