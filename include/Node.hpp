#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include "Vector2D.hpp"
#include "Cell.hpp"

/**
 * @class Node
 * @brief A class which represent a node in a Barnes-Hut tree.
 */

class Node {
public:
    enum class Quadrant { NW, NE, SW, SE };

    Node(const Cell& cell, Vector2D position)
        : cell(cell), position(position), totalMass(0.0), centerOfMass(Vector2D()) {}

    bool isLeaf() const {
        return children[0] == nullptr && children[1] == nullptr && children[2] == nullptr && children[3] == nullptr;
    }

    const Cell& getCell() const {
        return cell;
    }

    const Vector2D& getPosition() const {
        return position;
    }

    const std::vector<size_t>& getParticleIndices() const {
        return particleIndices;
    }

    void addParticleIndex(size_t index) {
        particleIndices.push_back(index);
    }

    Node::Quadrant getQuadrant(const std::vector<Vector2D>& positions, size_t index) const {
    const Vector2D& particlePosition = positions[index];
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

    const std::unique_ptr<Node>& getChild(Node::Quadrant quadrant) const {
        return children[static_cast<int>(quadrant)];
    }

    std::unique_ptr<Node>& getChild(Node::Quadrant quadrant) {
        return children[static_cast<int>(quadrant)];
    }

    void addChild(Node::Quadrant quadrant, std::unique_ptr<Node>&& child) {
        children[static_cast<int>(quadrant)] = std::move(child);
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

private:
    const Cell& cell;
    const Vector2D& position;
    std::vector<size_t> particleIndices;
    std::array<std::unique_ptr<Node>, 4> children;
    double totalMass;
    Vector2D centerOfMass;
};

#endif  // NODE_HPP
