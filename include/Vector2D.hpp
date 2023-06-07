#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>

/**
 * \brief Simple data type, meant to store information about pos, vel & acc for the Body object, also useful for storing force vector
 *
 * can be initialized via initializer list, so it can be initialized like this:
 * \code{.cpp}
 * long double x = 1;
 * long double y = 2.032324324e23;
 * newVector2D = Vector2D(x, y);
 * \endcode
 * implemented as header-only library
 */

class Vector2D{
public:
    Vector2D(long double x = 0, double y = 0) : x(x), y(y) {}

    double getNorm() const {
        double x2 = x * x;
        double y2 = y * y;
        return std::sqrt(x2 + y2);
    }

    Vector2D operator/(double m) const {
        Vector2D res;
        res.x = x / m;
        res.y = y / m;
        return res;
    }

    Vector2D operator+(const Vector2D &vec2) const {
        Vector2D res;
        res.x = x + vec2.x;
        res.y = y + vec2.y;
        return res;
    }

    Vector2D operator-(const Vector2D &vec2) const {
        Vector2D res;
        res.x = x - vec2.x;
        res.y = y - vec2.y;
        return res;
    }

    Vector2D operator*(double d) const {
        Vector2D res;
        res.x = x * d;
        res.y = y * d;
        return res;
    }

    double x;
    double y;
};

#endif // VECTOR2D_HPP
