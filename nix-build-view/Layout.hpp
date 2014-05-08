#ifndef LAYOUT__HPP
#define LAYOUT__HPP

#include "Widget.hpp"

class Layout {
public:
    Layout(/*unsigned int width, unsigned int height*/);
    void addWidget(Widget* w);
//     unsigned int width()  {
//         return m_width;
//     }
//     unsigned int height() {
//         return m_height;
//     }
    std::vector<Widget*> m_widgets;
// private:
//     unsigned int m_width = 0;
//     unsigned int m_height = 1;
};

#endif //LAYOUT__HPP
