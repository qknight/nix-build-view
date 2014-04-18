#ifndef COLORMANAGER_HPP
#define COLORMANAGER_HPP

#include <map>
#include <string>

class ColorManager {
public:
    int setColor(int fg, int bg);
private:
    std::map<std::string, int> m_map;
};

#endif // COLORMANAGER_HPP
