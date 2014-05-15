#ifndef WIDGETMANAGERBASE_H
#define WIDGETMANAGERBASE_H

#include "Widget.hpp"

template<typename TYPE>;

class WidgetManagerBase : public Widget {
public:
    static WidgetManagerBase* Instance();
    int type();
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    unsigned int rowsWantedByWidget();
private:
    WidgetManagerBase();
    std::vector<TYPE*> m_builds;
    int m_line = 0;
    void keyboardInputHandler(int ch);
    unsigned int width() {
        return m_width;
    }
    unsigned int height() {
        return m_height;
    }
    unsigned int m_width = 0;
    unsigned int m_height = 0;
};

#endif // WIDGETMANAGERBASE_H
