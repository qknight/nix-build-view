#ifndef COLORMANAGER_HPP
#define COLORMANAGER_HPP

#include <map>
#include <string>

// ncurses abstraction to make transparent use of attron(COLOR_PAIR(cm.setColor(color1, color2))) 
class ColorManager {
public:
    int setColor(int bg, int fg);
private:
    std::map<std::string, int> m_map;
};

#endif // COLORMANAGER_HPP
