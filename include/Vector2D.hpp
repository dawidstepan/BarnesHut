#ifndef GROUPMPROJECT_VECTOR2D_HPP
#define GROUPMPROJECT_VECTOR2D_HPP

/**
 * \brief Simple data type, meant to store information about pos, vel & acc for the Body object
 *
 * can be initialized via initializer list
 * implemented as header-only library
 */

class Vector2D{
public:
    Vector2D(long double x=0, long double y=0) : x(x), y(y) {
    }

    //overloading
    Vector2D operator/(int m){
        Vector2D res;
        res.x = x/m;
        res.y = y/m;
        return res;
    }
    long double x;
    long double y;
};

#endif //GROUPMPROJECT_VECTOR2D_HPP
