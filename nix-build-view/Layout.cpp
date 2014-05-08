#include "Layout.hpp"

Layout::Layout(/*unsigned int width, unsigned int height*/) {
//     m_width = width;
//     m_height = height;
}


void Layout::addWidget(Widget* w) {
    m_widgets.push_back(w);
}

// inputs to update:
//  - layout (list of widgets with size hints)
//  - widgets whishes (how many lines each widget wants to draw)
//
// layout schaut alle widgets durch:
//  - layout: HEIGHT size hint vom layout: FIXED, MINIMUM 1, RESIZE
//  - widget: wants height==3, draws nested widgets
// space which is not covered by a widget must be cleared
RasterizedLayout Layout::rasterize(int width, int height) {
    RasterizedLayout r;
    int rowsUsed = 0;
    for(unsigned int i=0; i < m_widgets.size(); ++i) {
        FixedWidget fw;
        fw.widget =  m_widgets[i];
        fw.height = 1;
        rowsUsed += fw.height;
        fw.width = width;
        r.m_fixedWidgets.push_back(fw);
    }
    // expand dynamic widgets
    if(rowsUsed < height)
        for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
            int t = r.m_fixedWidgets[i].widget->type();
            if (t == WidgetName::TerminalWidget || t == WidgetName::VerticalSpacerWidget) {
                int n = height - rowsUsed;
                r.m_fixedWidgets[i].height += n;
                rowsUsed += n;
            }
        }
    return r;
}
