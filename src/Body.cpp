# include "Body.hpp"

// getter- and setter functions
int Body::getSize() const {
    return size;
}

void Body::setSize(int size) {
    Body::size = size;
}

double Body::getWeight() const {
    return weight;
}

void Body::setWeight(double weight) {
    Body::weight = weight;
}

const Vector2D &Body::getPos() const {
    return pos;
}

void Body::setPos(const Vector2D &pos) {
    Body::pos = pos;
}

const Vector2D &Body::getVel() const {
    return vel;
}

void Body::setVel(const Vector2D &vel) {
    Body::vel = vel;
}

const Vector2D &Body::getAcc() const {
    return acc;
}

void Body::setAcc(const Vector2D &acc) {
    Body::acc = acc;
}