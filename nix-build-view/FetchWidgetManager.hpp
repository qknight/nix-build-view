#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class FetchWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static FetchWidgetManager* Instance();
private:
    FetchWidgetManager();
    void sort();
//     bool mySort(const Widget* a, const  Widget* b);
};

#endif // FETCHWIDGETMANAGER_H
