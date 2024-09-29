//
// Created by Jonathan on 27/09/2024.
//

#ifndef BRE_RECTANGLE_HPP
#define BRE_RECTANGLE_HPP

#include "Point2D.hpp"

struct Rectangle {
    unsigned short int x;
    unsigned short int y;
    unsigned short int w;
    unsigned short int h;
    unsigned short int Xmin() const { return x; }
    unsigned short int Ymin() const { return y; }
    unsigned short int Xmax() const { return x + w; }
    unsigned short int Ymax() const { return y + h; }

    Rectangle() : x(0), y(0), w(0), h(0) {}
    Rectangle(unsigned short int x, unsigned short int y, unsigned short int w, unsigned short int h) : x(x), y(y), w(w), h(h) {}

    Rectangle& operator=(const Rectangle& r) {
        x = r.x;
        y = r.y;
        w = r.w;
        h = r.h;
        return *this;
    }

    bool contains(const Point2D& p) const {
        return p.x >= Xmin() && p.x <= Xmax() && p.y >= Ymin() && p.y <= Ymax();
    }

    bool contains(unsigned short int x, unsigned short int y) const {
        return x >= Xmin() && x <= Xmax() && y >= Ymin() && y <= Ymax();
    }

    bool intersects(const Rectangle& r) const {
        return Xmin() < r.Xmax() && Xmax() > r.Xmin() && Ymin() < r.Ymax() && Ymax() > r.Ymin();
    }
};


#endif //BRE_RECTANGLE_HPP
