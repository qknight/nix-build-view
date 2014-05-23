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

    int size = m_url.size();
    AdvancedStringContainer url_progress;
    float end = m_percent * size;
    url_progress << AdvancedString(m_url.substr(0, (int)end), COLOR_GREEN) << m_url.substr((int)end, size-(int)end);

    //FIXME compute kib/Mib/Gib labels from input
    stringstream s1;
    s1 << setw(3) << right << (int)(m_percent*100) << "% " << setw(4) << setprecision(3) << 26.3333 << "Mib " << setw(4) << setprecision(4) << 123.31333 << "kib/s";
    AdvancedStringContainer s2;

    // dynamic spacer
    int i = width - url_progress.str_size() - s1.str().size() - 2;
    if (i < 0) i = 0;
    s2 << url_progress << " " << std::string(i, '.') << " " << AdvancedString(s1.str(), COLOR_YELLOW);

    return s2;
}
