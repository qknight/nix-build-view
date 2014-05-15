#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class FetchWidgetManager : public WidgetManagerBase {
public:
    int type();
    void add(const char* arg1, double arg2, int arg3);
};

#endif // FETCHWIDGETMANAGER_H
