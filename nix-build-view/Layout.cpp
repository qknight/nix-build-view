#include "Layout.hpp"

void Layout::addWidget(Widget* w, unsigned int heightHint) {
    m_layoutItems.push_back(new LayoutItem(w, heightHint));
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
    for(unsigned int i=0; i < m_layoutItems.size(); ++i) {
        FixedWidget fw;
        fw.widget = m_layoutItems[i]->widget;
        if (fw.widget->rowsWantedByWidget() == 0)
            fw.height = 0;
        else
            fw.height = 1;
        rowsUsed += fw.height;
        fw.width = width;
        r.m_fixedWidgets.push_back(fw);
    }


    // expand dynamic widgets
    if(rowsUsed < height)
        for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
            FixedWidget fw = r.m_fixedWidgets[i];
            int type = fw.widget->type();
            if (type == WidgetName::BuildWidgetManager || type == WidgetName::FetchWidgetManager) {
                int t = 0;
                int hH = 0;
                // search though the layout's highHint for the widget
                for(unsigned int i=0; i < m_layoutItems.size(); ++i) {
                    if (m_layoutItems[i]->widget == fw.widget) {
                        hH = m_layoutItems[i]->heightHint;
                    }
                }
                // use height given by widget unless the layout says it must be less
                if (fw.widget->rowsWantedByWidget() < hH)
                    t = fw.widget->rowsWantedByWidget();
                else
                    t = hH;
                // if t now exceeds the available height, we need to limit it to what is still available
                // marry x-mess code
                if (t > height - rowsUsed)
                    t = height - rowsUsed + 1; // FIXME why does +1 work here?
                if (t != 0)
                    rowsUsed += t-1; // FIXME why does -1 work here?
                fw.height = t;
                r.m_fixedWidgets[i] = fw;
            }
        }
    //FIXME this code can be consolidated
    // expand dynamic widgets
    if(rowsUsed < height)
        for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
            int type = r.m_fixedWidgets[i].widget->type();

            if (type == WidgetName::TerminalWidget) {
                int n = height - rowsUsed;
                r.m_fixedWidgets[i].height += n;
                rowsUsed += n;
            }
        }
    // expand help widgets
    if(rowsUsed < height)
        for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
            int type = r.m_fixedWidgets[i].widget->type();

            if (type == WidgetName::HelpWidget) {
                int n = height - rowsUsed;
                r.m_fixedWidgets[i].height += n;
                rowsUsed += n;
            }
        }
    // expand dynamic widgets
    if(rowsUsed < height)
        for(unsigned int i=0; i < r.m_fixedWidgets.size(); ++i) {
            int type = r.m_fixedWidgets[i].widget->type();

            if (type == WidgetName::VerticalSpacerWidget) {
                int n = height - rowsUsed;
                r.m_fixedWidgets[i].height += n;
                rowsUsed += n;
            }
        }
    return r;
}


