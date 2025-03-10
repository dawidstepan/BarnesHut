#ifndef GROUPMPROJECT_BODY_HPP
#define GROUPMPROJECT_BODY_HPP

#include "Vector2D.hpp"


/**
 * \brief the Body object represents the object our algorithm will act upon
 *
 * the Body object (like the Vector2D Object) possesses an initializer list, thus it can be conveniently initialized like this:
 * \code{.cpp}
 * newVector2D = Vector2D(0, 1);   // represents pos, vel & acc
 * newBody = Body(1, 2, newVector, newVector, newVector)   //object is now initialized and ready to use
 * \endcode
 * in addition, getter & setter functions are also present
 */
class Body{
public:
    Body(int size=0,
         double weight=0,
         Vector2D pos = Vector2D(0, 0),
         Vector2D vel = Vector2D(0, 0),
         Vector2D acc = Vector2D(0, 0)) :
         size(size),
         weight(weight),
         pos(pos),
         vel(vel),
         acc(acc) {

    };
    int getSize() const;

    void setSize(int size);

    double getWeight() const;

    void setWeight(double weight);

    const Vector2D &getPos() const;

    void setPos(const Vector2D &pos);

    const Vector2D &getVel() const;

    void setVel(const Vector2D &vel);

    const Vector2D &getAcc() const;

    void setAcc(const Vector2D &acc);

private:
    int size; //< radius in km
    double weight; //< weight in sun Masses
    Vector2D pos; //<position vector in Astronomical Units
    Vector2D vel; //<velocity vector in m/s
    Vector2D acc; //<acceleration vector in m/(s^2)
};


#endif //GROUPMPROJECT_BODY_HPP