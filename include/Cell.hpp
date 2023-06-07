#ifndef CELL_HPP
#define CELL_HPP

#include "Vector2D.hpp"

/**
 * @class Cell
 * @brief A class to represent a cell in a 2D space for a N-body simulation.
 */

class Cell {
public:
    Cell(const Vector2D& center, double length) : center(center), length(length) {}

    bool containsParticle(const Vector2D& particlecenter) const {
        double xMin = center.x - length / 2.0;
        double xMax = center.x + length / 2.0;
        double yMin = center.y - length / 2.0;
        double yMax = center.y + length / 2.0;

        return (particlecenter.x >= xMin && particlecenter.x <= xMax &&
                particlecenter.y >= yMin && particlecenter.y <= yMax);
    }

    Vector2D getMin() const {
        return Vector2D(center.x - length / 2.0, center.y - length / 2.0);
    }

    Vector2D getMax() const {
        return Vector2D(center.x + length / 2.0, center.y + length / 2.0);
    }

    double getLength() const {
        return length;
    }

    double getHalfLength() const {
        return length / 2.0;
    }

    const Vector2D getCenter() const {
        return center;
    }

private:
    Vector2D center;
    double length;
};

#endif  // CELL_HPP