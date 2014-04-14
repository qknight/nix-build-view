#ifndef WIDGET__HPP
#define WIDGET__HPP

#include "WindowManager.hpp"

#include <string>


class Widget {
public:
    virtual std::string render() = 0;
    void update() {
        WindowManager::Instance()->update();
    };
    unsigned int width()  {
        return m_width;
    };
    unsigned int height() {
        return m_height;
    };
    void resize(unsigned int width, unsigned int height) {
        m_width = width;
        m_height = height;
    }
private:
    unsigned int m_width = 0;
    unsigned int m_height = 1;
};

#endif
