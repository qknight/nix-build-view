#include "FetchWidgetManager.hpp"
#include "FetchWidget.hpp"

AdvancedStringContainer FetchWidgetManager::render(unsigned int width, unsigned int height) {
    AdvancedStringContainer s;
//     s << "BuildWidgetManager hello world: " << m_builds.size();
    for(unsigned int i=0; i < height; ++i) {
        if (i >= m_fetches.size())
            break;
        AdvancedStringContainer a = m_fetches[i]->render(width, 1);
        s << a;
    }
    return s;
}

int FetchWidgetManager::type() {
    return WidgetName::FetchWidgetManager;
}

FetchWidgetManager* FetchWidgetManager::Instance() {
    static FetchWidgetManager* _instance = new FetchWidgetManager;
    return _instance;
}

unsigned int FetchWidgetManager::rowsNeeded() {
    return m_fetches.size();
}

FetchWidgetManager::FetchWidgetManager() {

}

void FetchWidgetManager::add(const char* arg1, double arg2, int arg3) {
    m_fetches.push_back(new FetchWidget(arg1,arg2,arg3));
}
