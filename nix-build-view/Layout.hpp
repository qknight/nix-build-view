#ifndef LAYOUT__HPP
#define LAYOUT__HPP

#include "Widget.hpp"

class FixedWidget {

public:

    Widget* widget;
    unsigned int width  = 0;
    unsigned int height = 0;

};

class RasterizedLayout {

public:

    std::vector<FixedWidget> m_fixedWidgets;
};

class LayoutItem {

public:

    LayoutItem(Widget* w, unsigned int hH) {
        widget      = w;
        heightHint  = hH;
    }

    Widget* widget;
    unsigned int heightHint=1;
};


class Layout {

public:

    void addWidget(Widget* w, unsigned int sizeHint = 1);
    RasterizedLayout rasterize(int width, int height);

    //     unsigned int width()  {
    //         return m_width;
    //     }
    //     unsigned int height() {
    //         return m_height;
    //     }

    std::vector<LayoutItem*> m_layoutItems;

    // private:
    //     unsigned int m_width = 0;
    //     unsigned int m_height = 1;

};

#endif //LAYOUT__HPP
