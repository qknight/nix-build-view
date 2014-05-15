#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "Widget.hpp"


class FetchWidget;

class FetchWidgetManager : public Widget {
public:
    int type();
    void add(const char* arg1, double arg2, int arg3);
    static FetchWidgetManager* Instance();
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    unsigned int rowsWantedByWidget();
private:
    FetchWidgetManager();
    std::vector<FetchWidget*> m_fetches;
};

#endif // FETCHWIDGETMANAGER_H
