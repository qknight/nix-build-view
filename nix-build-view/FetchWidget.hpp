#ifndef FETCHWIDGET__HPP
#define FETCHWIDGET__HPP

#include "WindowManager.hpp"
#include "Widget.hpp"

class FetchWidget : public Widget {
public:
    FetchWidget(std::string url, float percent, int bits_per_sec);
    AdvancedStringContainer render(unsigned int width, unsigned int height);
    int type() const;
    std::string name() { return m_url; };
    float getProgress() const;
    void setProgress(float progress);
    void setBPS(int bits_per_sec);
    int getBPS();
private:
    float m_progress;
    std::string m_url;
    int m_bits_per_sec;
};

#endif
