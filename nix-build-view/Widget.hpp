#ifndef WIDGET__HPP
#define WIDGET__HPP

class Widget {
public:
    virtual std::string render(int w, int h) = 0;
};

#endif