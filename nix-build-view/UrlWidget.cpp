#include "UrlWidget.hpp"
#include <iostream>

#include <iostream>
#include <iomanip>
using namespace std;

UrlWidget::UrlWidget(std::string url, float percent, int bits_per_sec) {
    m_url=url;
    m_percent = percent;
    m_bits_per_sec = bits_per_sec;
};


std::string UrlWidget::render() {

    int size = m_url.size();
    std::stringstream url_progress;
    float end = m_percent * size;
    url_progress << m_url.substr(0, (int)end) << m_url.substr((int)end, size-(int)end);

    
    std::stringstream s1;
    s1 << " " << setw(3) << right << (int)(m_percent*100) << "% " << setw(4) << setprecision(4) << 123.31333 << "kib/s, " << setw(4) << setprecision(3) << 26.3333 << "Mib" << "\n";
    std::stringstream s2;
    
    // dynamic spacer
    int i = width() - url_progress.str().size() - s1.str().size() - 1;
    if (i < 0) i = 0;
    s2 << url_progress.str() << " " << std::string(i, '.') << s1.str();

    return s2.str();
}
