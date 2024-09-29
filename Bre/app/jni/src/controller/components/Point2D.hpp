//
// Created by Jonathan on 27/09/2024.
//

#ifndef BRE_POINT2D_HPP
#define BRE_POINT2D_HPP

#include <cmath>

struct Point2D {
    unsigned short int x;
    unsigned short int y;

    Point2D() : x(0), y(0) {}
    Point2D(unsigned short int x, unsigned short int y) : x(x), y(y) {}

    Point2D& operator=(const Point2D& p) {
        x = p.x;
        y = p.y;
        return *this;
    }

    float distance(const Point2D& p) const {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

#endif //BRE_POINT2D_HPP
