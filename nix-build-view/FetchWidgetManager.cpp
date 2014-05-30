#include "FetchWidgetManager.hpp"
#include "FetchWidget.hpp"
#include "TerminalWidget.hpp"

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

        return f1->getProgress() > f2->getProgress();
    }
    return false;
}

void FetchWidgetManager::sort() {
    std::stable_sort(m_widgets.begin(), m_widgets.end(), mySort);
}

void FetchWidgetManager::addFetch(std::string UUID, float progress, int bps) {
    add(new FetchWidget(UUID, progress, bps));
}

void FetchWidgetManager::removeFetch(std::string UUID) {

}

int FetchWidgetManager::getBPS(std::string UUID) {

}

float FetchWidgetManager::getProgress(std::string UUID) const {
    for(unsigned int i=0; i < m_widgets.size(); ++i) {
        FetchWidget* v = dynamic_cast<FetchWidget*>(FetchWidgetManager::Instance()->m_widgets[i]);
        if (v->name() == UUID) {
            return v->getProgress();
        }
    }
}

void FetchWidgetManager::setBPS(std::string UUID, int bits_per_sec) {

}

void FetchWidgetManager::setProgress(std::string UUID, float progress) {
    for(unsigned int i=0; i < m_widgets.size(); ++i) {
        FetchWidget* v = dynamic_cast<FetchWidget*>(m_widgets[i]);
        if (v->name() == UUID) {
            v->setProgress(progress);
            if (progress >= 1.0f) {
                AdvancedStringContainer v;
                v << "download of " << AdvancedString(UUID, COLOR_GREEN) << " completed\n";
                TerminalWidget::Instance()->append(v);
                sort();
                m_widgets.erase(m_widgets.begin());
                update();
            }
            return;
        }
    }
}
