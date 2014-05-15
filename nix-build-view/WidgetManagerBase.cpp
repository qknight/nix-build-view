#include "WidgetManagerBase.hpp"

AdvancedStringContainer WidgetManagerBase::render(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;
    
    AdvancedStringContainer s;
    for(unsigned int i=m_line; i < m_line+height; ++i) {
        if (i >= m_builds.size())
            break;
        AdvancedStringContainer a = m_builds[i]->render(width, 1);
        s << a;
    }
    return s;
}

unsigned int WidgetManagerBase::rowsWantedByWidget() {
    return m_builds.size();
}

WidgetManagerBase* WidgetManagerBase::Instance() {
    static WidgetManagerBase* _instance = new WidgetManagerBase;
    return _instance;
}

WidgetManagerBase::WidgetManagerBase() {
}

void WidgetManagerBase::keyboardInputHandler(int ch) {
    switch(ch) {
    case(KEY_HOME): 
        m_line = 0;
        update();
        break;
    case(KEY_END):
        m_line = m_builds.size()-height();
        update();
        break;
    case(KEY_UP):
        m_line -= 1;
        if (m_line < 0)
            m_line = 0;
        update();
        break;
    case(KEY_DOWN):
        if (m_line >= 0)
            m_line += 1;
        if(m_line > m_builds.size()-height())
            m_line = m_builds.size()-height();
        update();
        break;
    case(KEY_PPAGE):
        m_line -= 15;
        if (m_line < 0)
            m_line = 0;
        update();
        break;
    case(KEY_NPAGE):
        if (m_line >= 0)
            m_line += 15;
        if(m_line > m_builds.size()-height())
            m_line = m_builds.size()-height();
        update();
        break;
    default:
        break;
    }
}
