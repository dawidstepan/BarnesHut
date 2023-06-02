#include "BarnesHut.hpp"
#include "Node.hpp"
#include "Units.hpp"
#include "Body.hpp"
#include <cmath>

BarnesHut::BarnesHut(const std::vector<Body> &body, double theta, double lengthOfSpace)
    : body(body), theta(theta) {}

std::unique_ptr<Node> BarnesHut::buildTree(const std::vector<Body> &body, double lengthOfSpace) {
    // Initialize a root node
    Vector2D position(0.0, 0.0);
    Cell rootCell(position, lengthOfSpace);
    int level;
    auto rootNode = std::make_unique<Node>(rootCell, position, level);

    for (size_t i = 0; i < body.size(); i++) {
        // Recursive process that add particles into the tree
        addParticle(rootNode, body, i);
    }

    return rootNode;
}

void BarnesHut::addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) {
    if (node->isLeaf()) {
        if (node->getParticleIndices().empty()) {
            node->addParticleIndex(index);
            updateMassAndCenterOfMass(node, body, index);
        } else {
            /*
            // Generates four child nodes everytime when they missing and thus also redundant child nodes
            for (int quadrant = 0; quadrant < 4; quadrant++) {
                Vector2D childPosition = node->setChildPosition(quadrant);
                Cell childCell(childPosition, node->getCell().getHalfLength());
                node->addChild(quadrant, std::make_unique<Node>(childCell, childPosition));
            }

            int oldIndex = node->getParticleIndices().front();
            node->getParticleIndices().clear();
            Node::Quadrant oldQuadrant = node->getQuadrant(body[oldIndex].getPos());
            addParticle(node->getChild(oldQuadrant), body, oldIndex);

            // Add new particle to appropriate child node
            Node::Quadrant newQuadrant = node->getQuadrant(body[index].getPos());
            addParticle(node->getChild(newQuadrant), body, index);
            */
            int oldIndex = node->getParticleIndices().front();
            node->getParticleIndices().clear();
            
            Node::Quadrant oldQuadrant = node->getQuadrant(body[oldIndex].getPos());
            Vector2D bodyPosition = body[index].getPos();
            if (!node->getChild(oldQuadrant)) {
                Vector2D childPosition = node->setChildPosition(static_cast<int>(oldQuadrant));
                Cell childCell(childPosition, node->getCell().getHalfLength());
                node->addChild(static_cast<int>(oldQuadrant), std::make_unique<Node>(childCell, bodyPosition, node->getLevel() + 1));
            }
            addParticle(node->getChild(oldQuadrant), body, oldIndex);

            // Add new particle to appropriate child node
            Node::Quadrant newQuadrant = node->getQuadrant(body[index].getPos());
            if (!node->getChild(newQuadrant)) {
                Vector2D childPosition = node->setChildPosition(static_cast<int>(newQuadrant));
                Cell childCell(childPosition, node->getCell().getHalfLength());
                node->addChild(static_cast<int>(newQuadrant), std::make_unique<Node>(childCell, bodyPosition, node->getLevel() + 1));
            }    
            addParticle(node->getChild(newQuadrant), body, index);
        }
    } else {
        Node::Quadrant quadrant = node->getQuadrant(body[index].getPos());
        Vector2D bodyPosition = body[index].getPos();

        if (!node->getChild(quadrant)) {
            Vector2D childPosition = node->setChildPosition(static_cast<int>(quadrant));
            Cell childCell(childPosition, node->getCell().getHalfLength());
            node->addChild(static_cast<int>(quadrant), std::make_unique<Node>(childCell, bodyPosition, node->getLevel() + 1));
        }
        addParticle(node->getChild(quadrant), body, index);
    }
}

void BarnesHut::updateMassAndCenterOfMass(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) {
    double oldMass = node->getTotalMass();
    Vector2D oldCenterOfMass = node->getCenterOfMass();
    Vector2D newCenterOfMass;

    double newMass = oldMass + body[index].getWeight();
    newCenterOfMass.x = (oldCenterOfMass.x * oldMass + body[index].getPos().x * body[index].getWeight()) / newMass;
    newCenterOfMass.y = (oldCenterOfMass.y * oldMass + body[index].getPos().y * body[index].getWeight()) / newMass;
    
    node->setTotalMass(newMass);
    node->setCenterOfMass(newCenterOfMass);
}

Vector2D BarnesHut::calculateForce(const Node& node, const Vector2D& bodyPosition) {
    // Implement the force calculation algorithm using the tree 
}

Vector2D BarnesHut::getForceByNaiveAlgorithm(const std::vector<Vector2D>& bodies) {
    // Implement the naive force calculation algorithm 
}