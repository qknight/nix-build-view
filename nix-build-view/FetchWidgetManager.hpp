#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class FetchWidgetManager : public WidgetManagerBase {
public:
    int type();
    static FetchWidgetManager* Instance();
private:
    FetchWidgetManager();
};

#endif // FETCHWIDGETMANAGER_H
