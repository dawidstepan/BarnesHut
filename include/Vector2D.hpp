#ifndef GROUPMPROJECT_VECTOR2D_HPP
#define GROUPMPROJECT_VECTOR2D_HPP

/**
 * \brief Simple data type, meant to store information about pos, vel & acc for the Body object
 *
 * can be initialized via initializer list
 */

class Vector2D{
public:
    Vector2D(double x=0, double y=0) : x(x), y(y) {
    }

    //overloading
    Vector2D operator/(int m){
        x = x/m;
        y = y/m;
    }
    double x;
    double y;
};

#endif //GROUPMPROJECT_VECTOR2D_HPP
