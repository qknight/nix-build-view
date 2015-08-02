#include "WidgetManagerBase.hpp"

AdvancedStringContainer
WidgetManagerBase::render(unsigned int width, unsigned int height)
{
    m_width     = width;
    m_height    = height;

    sort();

    // if elements vanish you don't have to scroll up manually
    if(m_line > m_widgets.size() - height) {
        m_line = m_widgets.size() - height;
    }

    AdvancedStringContainer sc;
    for (unsigned int i = m_line; i < m_line+height; ++i) {
        if (i >= m_widgets.size()) {
            break;
        }

        AdvancedStringContainer a = m_widgets[i]->render(width, 1);

        // limits the stringsize to width (if it was longer)
        int left = width * 1;
        for (unsigned int x = 0; x < a.size(); ++x) {
            if(!left) {
                break;
            }

            AdvancedString as;
            if (left < a[x].size()) {
                as = AdvancedString::substr(a[x], 0, left);
            } else {
                as = a[x];
            }

            sc << as;
            left -= as.size();
        }
    }

    return sc;
}

unsigned int
WidgetManagerBase::rowsWantedByWidget()
{
    return m_widgets.size();
}

void
WidgetManagerBase::keyboardInputHandler(int ch)
{
    switch(ch) {
    case(KEY_HOME):
        m_line = 0;
        update();
        break;

    case(KEY_END):
        m_line = m_widgets.size()-height();
        update();
        break;

    case(KEY_UP):
        m_line -= 1;
        if (m_line < 0) {
            m_line = 0;
        }
        update();
        break;

    case(KEY_DOWN):
        if (m_line >= 0) {
            m_line += 1;
        }

        if(m_line > m_widgets.size() - height()) {
            m_line = m_widgets.size() - height();
        }
        update();
        break;

    case(KEY_PPAGE):
        m_line -= 15;
        if (m_line < 0) {
            m_line = 0;
        }
        update();
        break;

    case(KEY_NPAGE):
        if (m_line >= 0) {
            m_line += 15;
        }

        if (m_line > m_widgets.size() - height()) {
            m_line = m_widgets.size() - height();
        }

        update();
        break;

    default:
        break;

    }
}

void
WidgetManagerBase::add(Widget* w)
{
    m_widgets.push_back(w);
    sort();
    update();
}

