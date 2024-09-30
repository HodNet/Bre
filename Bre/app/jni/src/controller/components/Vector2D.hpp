//
// Created by Jonathan on 27/09/2024.
//

#ifndef BRE_VECTOR2D_HPP
#define BRE_VECTOR2D_HPP

#include <cmath>

struct Vector2D {
    float x;
    float y;

    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

    Vector2D& operator=(const Vector2D& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vector2D operator+(const Vector2D& v) const {
        return Vector2D(x + v.x, y + v.y);
    }

    Vector2D operator-(const Vector2D& v) const {
        return Vector2D(x - v.x, y - v.y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator/(float scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    Vector2D& operator+=(const Vector2D& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vector2D& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    float operator*(const Vector2D& v) const {
        return x * v.x + y * v.y;
    }

    float getMagnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2D normalize() const {
        return *this / magnitude();
    }

    double getAngle() const {
        return atan2(y, x);
    }
};

#endif //BRE_VECTOR2D_HPP
