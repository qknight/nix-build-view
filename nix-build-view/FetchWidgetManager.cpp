#include "FetchWidgetManager.hpp"

int FetchWidgetManager::type() {
    return WidgetName::BuildWidgetManager;
}

void FetchWidgetManager::add(const char* arg1, double arg2, int arg3) {
    m_fetches.push_back(new FetchWidget(arg1,arg2,arg3));
}
