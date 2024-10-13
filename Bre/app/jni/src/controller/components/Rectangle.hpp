//
// Created by Jonathan on 27/09/2024.
//

#ifndef BRE_RECTANGLE_HPP
#define BRE_RECTANGLE_HPP

#include "Point2D.hpp"

struct Rectangle {
    float x;
    float y;
    float w;
    float h;
    float Xmin() const { return x; }
    float Ymin() const { return y; }
    float Xmax() const { return x + w; }
    float Ymax() const { return y + h; }

    Rectangle() : x(0), y(0), w(0), h(0) {}
    Rectangle(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

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

    bool contains(float x, float y) const {
        return x >= Xmin() && x <= Xmax() && y >= Ymin() && y <= Ymax();
    }

    bool intersects(const Rectangle& r) const {
        return Xmin() < r.Xmax() && Xmax() > r.Xmin() && Ymin() < r.Ymax() && Ymax() > r.Ymin();
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }
};


#endif //BRE_RECTANGLE_HPP
