#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include "Vector2D.hpp"
#include "Cell.hpp"

/**
 * @class Node
 * @brief A class which represent a node in a Barnes-Hut tree for a N-body simulation.
 */

class Node {
public:
    enum class Quadrant {
        NW, 
        NE, 
        SW, 
        SE
    };

    Node(Cell& cell, Vector2D& position, int level)
        : cell(cell), position(position), level(level), totalMass(0.0), centerOfMass(Vector2D(0,0)) {}

    bool isLeaf() const {
        return children[0] == nullptr 
            && children[1] == nullptr 
            && children[2] == nullptr 
            && children[3] == nullptr;
    }

    const Cell& getCell() const {
        return cell;
    }

    const Vector2D& getPosition() const {
        return position;
    }

    std::vector<size_t>& getParticleIndices() {
        return particleIndices;
    }

    void addParticleIndex(size_t index) {
        particleIndices.push_back(index);
    }

    Node::Quadrant getQuadrant(const Vector2D& particlePosition) const {
        Vector2D cellMidPoint = (cell.getMin() + cell.getMax()) / 2.0;

        if (particlePosition.x <= cellMidPoint.x) {
            if (particlePosition.y <= cellMidPoint.y) {
                return Node::Quadrant::SW;
            } else {
                return Node::Quadrant::NW;
            }
        } else {
            if (particlePosition.y <= cellMidPoint.y) {
                return Node::Quadrant::SE;
            } else {
                return Node::Quadrant::NE;
            }
        }
    }

    Vector2D setChildPosition(int quadrant) const {
        double halfLength = this->getCell().getHalfLength();
        Vector2D childPosition;

        switch (quadrant) {
        case 0: // NW
            childPosition = Vector2D(cell.getCenter().x - halfLength, cell.getCenter().y + halfLength);
            break;
        case 1: // NE
            childPosition = Vector2D(cell.getCenter().x + halfLength, cell.getCenter().y + halfLength);
            break;
        case 2: // SW
            childPosition = Vector2D(cell.getCenter().x - halfLength, cell.getCenter().y - halfLength);
            break;
        case 3: // SE
            childPosition = Vector2D(cell.getCenter().x + halfLength, cell.getCenter().y - halfLength);
            break;
        default:
            throw std::invalid_argument("Invalid quadrant");
        }

        return childPosition;
    }

    const std::unique_ptr<Node>& getChild(Node::Quadrant quadrant) const {
        return children[static_cast<int>(quadrant)];
    }

    std::unique_ptr<Node>& getChild(Node::Quadrant quadrant) {
        return children[static_cast<int>(quadrant)];
    }

    void addChild(int quadrant, std::unique_ptr<Node>&& child) {
        children[quadrant] = std::move(child);
    }

    double getTotalMass() const {
        return totalMass;
    }

    void setTotalMass(double mass) {
        totalMass = mass;
    }

    const Vector2D& getCenterOfMass() const {
        return centerOfMass;
    }

    void setCenterOfMass(const Vector2D& center) {
        centerOfMass = center;
    }

    int getLevel() const {
        return level;
    }

private:
    int level = 0;
    Cell cell;
    Vector2D position;
    std::vector<size_t> particleIndices;
    std::array<std::unique_ptr<Node>, 4> children;
    double totalMass;
    Vector2D centerOfMass;
};

#endif // NODE_HPP
