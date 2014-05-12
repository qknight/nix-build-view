#include "FetchWidgetManager.hpp"

AdvancedStringContainer FetchWidgetManager::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
    s << "FetchWidgetManager hello world";
    return s;
}

int FetchWidgetManager::type() {
    return WidgetName::FetchWidgetManager;
}

FetchWidgetManager* FetchWidgetManager::Instance() {
    static FetchWidgetManager* _instance = new FetchWidgetManager;
    return _instance;
}

FetchWidgetManager::FetchWidgetManager()
{

}
