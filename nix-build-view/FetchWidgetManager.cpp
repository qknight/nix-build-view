#include "FetchWidgetManager.hpp"

#include <iostream>
#include <algorithm>

FetchWidgetManager::FetchWidgetManager() {
}

int FetchWidgetManager::type() {
    return WidgetName::FetchWidgetManager;
}

FetchWidgetManager* FetchWidgetManager::Instance() {
    static FetchWidgetManager* _instance = new FetchWidgetManager;
    return _instance;
}

void FetchWidgetManager::sort() {
}