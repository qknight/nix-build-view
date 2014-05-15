#include "BuildWidgetManager.hpp"
#include "BuildWidget.hpp"

AdvancedStringContainer BuildWidgetManager::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
//     s << "BuildWidgetManager hello world: " << m_builds.size();
    for(unsigned int i=0; i < height; ++i) {
        if (i >= m_builds.size())
            break;
        AdvancedStringContainer a = m_builds[i]->render(width, 1);
        s << a;
    }
    return s;
}

int BuildWidgetManager::type() {
    return WidgetName::BuildWidgetManager;
}

unsigned int BuildWidgetManager::rowsNeeded() {
    return m_builds.size();
}

BuildWidgetManager* BuildWidgetManager::Instance() {
    static BuildWidgetManager* _instance = new BuildWidgetManager;
    return _instance;
}

BuildWidgetManager::BuildWidgetManager() {

}

void BuildWidgetManager::add(const char* arg1, const char* arg2) {
    m_builds.push_back(new BuildWidget(arg1, arg2));
}

