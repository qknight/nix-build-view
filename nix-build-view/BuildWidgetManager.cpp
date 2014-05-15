#include "BuildWidgetManager.hpp"

int BuildWidgetManager::type() {
    return WidgetName::BuildWidgetManager;
}

void BuildWidgetManager::add(const char* arg1, const char* arg2) {
    m_builds.push_back(new BuildWidget(arg1, arg2));
}