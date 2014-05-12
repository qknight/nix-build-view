#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "Widget.hpp"

class FetchWidgetManager : public Widget {
public:
    int type();
    static FetchWidgetManager* Instance();
    AdvancedStringContainer render(unsigned int width, unsigned int height);
private:
    FetchWidgetManager();
};

#endif // FETCHWIDGETMANAGER_H
