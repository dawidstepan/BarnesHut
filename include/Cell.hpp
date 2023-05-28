#ifndef CELL_HPP
#define CELL_HPP

#include "Vector2D.hpp"

/**
 * @class Cell
 * @brief A class which represent a cell in a 2D space.
 */

class Cell {
public:
    Cell(const Vector2D& position, double length) : position(position), length(length) {}

    bool containsParticle(size_t index, const std::vector<Vector2D>& positions) const {
        const Vector2D& particlePosition = positions[index];
        double xMin = position.x - length / 2;
        double xMax = position.x + length / 2;
        double yMin = position.y - length / 2;
        double yMax = position.y + length / 2;

        return (particlePosition.x >= xMin && particlePosition.x <= xMax &&
                particlePosition.y >= yMin && particlePosition.y <= yMax);
    }

    Vector2D getMin() const {
        return Vector2D(position.x - length / 2, position.y - length / 2);
    }

    Vector2D getMax() const {
        return Vector2D(position.x + length / 2, position.y + length / 2);
    }

    double getLength() const {
        return length;
    }

private:
    Vector2D position;
    double length;
};

#endif  // CELL_HPP