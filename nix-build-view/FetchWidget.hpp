#ifndef FETCHWIDGET__HPP
#define FETCHWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class FetchWidget : public Widget {

    friend class FetchWidgetManager;

public:

    FetchWidget(std::string url, float percent, int bits_per_sec);

    AdvancedStringContainer render(unsigned int width, unsigned int height);

    int type() const;

    float getProgress() const;

private:

    float m_progress;

    std::string m_name;

    int m_bits_per_sec;

};

#endif // FETCHWIDGET__HPP
