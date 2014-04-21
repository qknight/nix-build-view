#include "UrlWidget.hpp"
#include "AdvancedString.hpp"

#include <iostream>
#include <iostream>
#include <iomanip>
using namespace std;

UrlWidget::UrlWidget(std::string url, float percent, int bits_per_sec) {
    m_url=url;
    m_percent = percent;
    m_bits_per_sec = bits_per_sec;
};

AdvancedStringContainer UrlWidget::render() {

    int size = m_url.size();
    AdvancedStringContainer url_progress;
    float end = m_percent * size;
    url_progress << AdvancedString(m_url.substr(0, (int)end), COLOR_GREEN) << m_url.substr((int)end, size-(int)end);

    
    AdvancedStringContainer s1;
//     s1 << " " << setw(3) << right << (int)(m_percent*100) << "% " << setw(4) << setprecision(4) << 123.31333 << "kib/s " << setw(4) << setprecision(3) << 26.3333 << "Mib" << "\n";
    s1 << " " << (int)(m_percent*100) << "/100 " << 123.31333f << "kib/s " << 26.3333f << "Mib" << "\n";
    AdvancedStringContainer s2;
    
    // dynamic spacer
    int i = width() - url_progress.str_size() - s1.str_size() ;
    if (i < 0) i = 0;
    s2 << url_progress << " " << std::string(i, '.') << s1;
    return s2;
}
