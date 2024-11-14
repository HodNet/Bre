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
    Point2D(const unsigned short int x, const unsigned short int y) : x(x), y(y) {}
    Point2D(const int x, const int y) : x(x), y(y) {}
    Point2D(const float x, const float y) : x(static_cast<unsigned short int>(x)), y(static_cast<unsigned short int>(y)) {}
    Point2D(const Point2D& p) : x(p.x), y(p.y) {}

    float distance(const Point2D& p) const {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }

    Point2D& operator=(const Point2D& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};

#endif //BRE_POINT2D_HPP
