#include "FetchWidget.hpp"
#include "AdvancedString.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

FetchWidget::FetchWidget(std::string url, float percent, int bits_per_sec) {
    m_url=url;
    m_percent = percent;
    m_bits_per_sec = bits_per_sec;
};

int FetchWidget::type() const {
    return WidgetName::FetchWidget;
}


AdvancedStringContainer FetchWidget::render(unsigned int width, unsigned int height) {

    AdvancedStringContainer url_progress;


    //FIXME compute kib/Mib/Gib labels from input
    stringstream s1;
    s1 << setw(3) << right << (int)(m_percent*100) << "% " << setw(4) << setprecision(3) << 26.3333 << "Mib " << setw(4) << setprecision(4) << 123.31333 << "kib/s";
    AdvancedStringContainer s2;

    // dynamic spacer
    int i = width - m_url.size() - s1.str().size() - 1;
    if (i < 0) i = 0;

    std::stringstream t;
    t << m_url << " " << std::string(i+1, '.');

    int size = t.str().size()-2;
    float end = m_percent * size;

    url_progress << AdvancedString(t.str().substr(0, (int)end), COLOR_GREEN) << t.str().substr((int)end, size-(int)end);
    s2 << url_progress << " " << AdvancedString(s1.str(), COLOR_YELLOW);

    return s2;
}
