#include "FetchWidgetManager.hpp"

FetchWidgetManager::FetchWidgetManager() {
}

int FetchWidgetManager::type() {
    return WidgetName::FetchWidgetManager;
}

FetchWidgetManager* FetchWidgetManager::Instance() {
    static FetchWidgetManager* _instance = new FetchWidgetManager;
    return _instance;
}
