#ifndef STATUSWIDGET__HPP
#define STATUSWIDGET__HPP

#include "Widget.hpp"

class StatusWidget : public Widget {

    AdvancedStringContainer render(unsigned int width, unsigned int height);

public:

    void setFocus(int arg1);

    int type() const;

    static StatusWidget* Instance();

    void setBuilds(unsigned int builds);

    void setFetches(unsigned int fetches);

private:

    StatusWidget();

    unsigned int m_focus    = 1;
    unsigned int m_builds   = 0;
    unsigned int m_fetches  = 0;

};

#endif // STATUSWIDGET__HPP
