#include "BarnesHut.hpp"
#include "Node.hpp"
#include "Units.hpp"
#include "Body.hpp"
#include <cmath>
#include <iostream>

BarnesHut::BarnesHut(const std::vector<Body>& body, double theta, double lengthOfSpace)
    : body(body), theta(theta),lengthOfSpace(lengthOfSpace) {}

std::unique_ptr<Node> BarnesHut::buildTree() {
    // Initialize a root node
    Vector2D position(0.0, 0.0);
    Cell rootCell(position, lengthOfSpace);
    int level = 0;
    auto rootNode = std::make_unique<Node>(rootCell, position, level);

    for (size_t i = 0; i < body.size(); i++) {
        // Recursive process that add particles into the tree
        addParticle(rootNode, body, i);
    }
    return rootNode;
}

std::vector<Vector2D> BarnesHut::calculateForce() {
/*  Test
    // Get the tree structure
    std::unique_ptr<Node> node = buildTree();
    std::vector<Vector2D> forces(body.size());

    // Calculate forces
    for(size_t i = 0; i < body.size(); i++) {
        forces[i] = calculateForceFromNode(node, body, i);
        // Store calculated force
    }
    return forces;
*/  
    std::vector<Vector2D> test;
    return test;
}

void BarnesHut::addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) {
    if (node->isLeaf()) {
        if (node->getParticleIndices().empty()) {
            node->addParticleIndex(index);
            //node->setTotalMass(body[index].getWeight());
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
            double oldMass = node->getTotalMass();
            Vector2D oldCenterOfMass = node->getCenterOfMass();
            
            Node::Quadrant oldQuadrant = node->getQuadrant(body[oldIndex].getPos());
            
            if (!node->getChild(oldQuadrant)) {
                Vector2D childPosition = node->setChildPosition(static_cast<int>(oldQuadrant));
                Vector2D bodyPosition = body[oldIndex].getPos();
                Cell childCell(childPosition, node->getCell().getHalfLength());
                node->addChild(static_cast<int>(oldQuadrant), std::make_unique<Node>(childCell, bodyPosition, node->getLevel() + 1));
            }
            addParticle(node->getChild(oldQuadrant), body, oldIndex);

            // Add new particle to appropriate child node
            Node::Quadrant newQuadrant = node->getQuadrant(body[index].getPos());
            if (!node->getChild(newQuadrant)) {
                Vector2D childPosition = node->setChildPosition(static_cast<int>(newQuadrant));
                Vector2D bodyPosition = body[index].getPos();
                Cell childCell(childPosition, node->getCell().getHalfLength());
                node->addChild(static_cast<int>(newQuadrant), std::make_unique<Node>(childCell, bodyPosition, node->getLevel() + 1));
            }    
            addParticle(node->getChild(newQuadrant), body, index);
            updateMassAndCenterOfMass(node, body, index);

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
        updateMassAndCenterOfMass(node, body, index);

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

Vector2D BarnesHut::calculateBruteForce(size_t particleIndex1, size_t particleIndex2) const {
    Vector2D direction = body[particleIndex1].getPos() - body[particleIndex2].getPos();
    double distance = direction.getNorm();
    double magnitude = (G * body[particleIndex1].getWeight() * body[particleIndex2].getWeight()) / (distance * distance);

    if (distance < 1.0e-100)
        distance = 1.0e-100;
    return (direction / distance) * magnitude;
}

/*
// Test
Vector2D BarnesHut::calculateForceFromNode(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) const {
    if(node->isLeaf()) { 
        return calculateForceFromParticle(body, node->getParticleIndices()[0], index);
    } else {
        Vector2D force(0, 0);
        Vector2D bodyPosition = body[index].getPos();
        double bodyWeigth = body[index].getWeight(); 

        for(int i = 0; i < 4; i++) {
            std::unique_ptr<Node>& child = node->getChild(static_cast<Node::Quadrant>(i));
            if(child) {
                double distance = (child->getCenterOfMass() - bodyPosition).getNorm();
                if (node->getCell().getLength() / distance < theta ) {
                    Vector2D direction = child->getCenterOfMass() - bodyPosition;
                    double magnitude = (G * child->getTotalMass() * bodyWeigth) / (distance * distance);
                    force = force + direction * magnitude;
                } else {
                    force = force + calculateForceFromNode(child, body, index);
                }
            }
        }
        return force;
    }
}

Vector2D BarnesHut::calculateForceFromParticle(const std::vector<Body>& body, size_t particleIndex1, size_t particleIndex2) const { 
    Vector2D force(0, 0);

    Body particle1 = body[particleIndex1];
    Body particle2 = body[particleIndex2];

    Vector2D direction = particle1.getPos() - particle2.getPos();
    double distance = direction.getNorm();

    double magnitude = (G * particle1.getWeight() * particle2.getWeight()) / (distance * distance);

    if (distance > 1.0e-100) {
        force = direction / distance * magnitude;    
    } else {
        force = Vector2D(0, 0);
    } 
    return force;
}
*/
