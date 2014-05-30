#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class FetchWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static FetchWidgetManager* Instance();
//     void add(std::string UUID);
//     void remove(std::string UUID);
private:
    FetchWidgetManager();
    void sort();
};

#endif // FETCHWIDGETMANAGER_H
