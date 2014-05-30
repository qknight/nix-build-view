#ifndef FETCHWIDGETMANAGER_H
#define FETCHWIDGETMANAGER_H

#include "WidgetManagerBase.hpp"

class FetchWidgetManager : public WidgetManagerBase {
public:
    int type() const;
    static FetchWidgetManager* Instance();
    void addFetch(std::string UUID, float progress, int bps);
    void removeFetch(std::string UUID);
    float getProgress(std::string UUID) const;
    void setProgress(std::string UUID, float progress);
    int getBPS(std::string UUID);
    void setBPS(std::string UUID, int bits_per_sec);
private:
    FetchWidgetManager();
    void sort();
};

#endif // FETCHWIDGETMANAGER_H
