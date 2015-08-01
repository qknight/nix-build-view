#ifndef WIDGETMANAGERBASE_H
#define WIDGETMANAGERBASE_H

#include "Widget.hpp"

class WidgetManagerBase : public Widget {

    friend class FetchWidgetManager;
    friend class BuildWidgetManager;

public:

    virtual int type() const = 0;

    AdvancedStringContainer render(unsigned int width, unsigned int height);

    unsigned int rowsWantedByWidget();

private:

    void add(Widget* w);

    std::vector<Widget*> m_widgets;

    int m_line = 0;

    void keyboardInputHandler(int ch);

    unsigned int width() {
        return m_width;
    }

    unsigned int height() {
        return m_height;
    }

    unsigned int m_width    = 0;
    unsigned int m_height   = 0;
    virtual void sort()     = 0;
};

#endif // WIDGETMANAGERBASE_H
