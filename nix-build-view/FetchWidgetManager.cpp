#include "FetchWidgetManager.hpp"
#include "FetchWidget.hpp"

#include <iostream>
#include <algorithm>

FetchWidgetManager::FetchWidgetManager() {
}

int FetchWidgetManager::type() const {
    return WidgetName::FetchWidgetManager;
}

FetchWidgetManager* FetchWidgetManager::Instance() {
    static FetchWidgetManager* _instance = new FetchWidgetManager;
    return _instance;
}

bool mySort(const Widget* a, const  Widget* b) {
    if ((a->type() == WidgetName::FetchWidget) && (b->type() == WidgetName::FetchWidget)) {
        const FetchWidget* f1 = dynamic_cast<const FetchWidget*>(a);
        const FetchWidget* f2 = dynamic_cast<const FetchWidget*>(b);

        return f1->m_percent > f2->m_percent;
    }
    return false;
}

void FetchWidgetManager::sort() {
    std::stable_sort(m_widgets.begin(), m_widgets.end(), mySort);
}
