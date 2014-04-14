#ifndef WIDGET__HPP
#define WIDGET__HPP

#include <string>

class Widget {
public:
    virtual std::string render(int w, int h) = 0;
//     virtual void update() = 0;
};

#endif