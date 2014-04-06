#include "UrlWidget.hpp"

UrlWidget::UrlWidget(std::string url, float percent, int bits_per_sec) {
    m_url=url;
    m_percent = percent;
    m_bits_per_sec = bits_per_sec;
};

std::string UrlWidget::render(int w, int h) {
    std::stringstream s;

    int size = m_url.size();
    std::stringstream url_progress;
    float end = m_percent * size;
    url_progress << m_url.substr(0, (int)end) << m_url.substr((int)end, size-(int)end);

    s << url_progress.str() << " " << (int)(m_percent*100) << "% " << m_bits_per_sec << "\n";
    return s.str();
}
