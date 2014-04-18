#include "ColorManager.hpp"
#include "ncurses.h"


int ColorManager::setColor(int fg, int bg) {
    std::string key = std::to_string(fg) + std::to_string(bg);

    std::map<std::string, int>::iterator pos = m_map.find(key);
    if (pos == m_map.end()) {
        m_map.insert(std::make_pair(key, m_map.size()));
        init_pair(m_map.size(), fg, bg);
        return m_map.size();
    } else {
        return pos->second+1;
    }
}
