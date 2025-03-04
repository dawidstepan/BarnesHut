#include "BarnesHut.hpp"
#include "Node.hpp"
#include "Units.hpp"
#include "Body.hpp"
#include <cmath>
#include <iostream>

BarnesHut::BarnesHut(const std::vector<Body>& body, float theta)
    : body(body), theta(theta) {}

double BarnesHut::getMaxCoordinate(const std::vector<Body>& bodyVector) {
    double maxX = 0.0;
    double maxY = 0.0;

    for (const auto& body : bodyVector) {
        double posX = body.getPos().x;
        double posY = body.getPos().y;

        maxX = std::max(maxX, std::abs(posX));
        maxY = std::max(maxY, std::abs(posY));
    }
    return std::max(maxX, maxY);
}

std::unique_ptr<Node> BarnesHut::buildTree() {
    // Initialize a root node
    Vector2D position(0.0, 0.0);
    double lengthOfSpace = getMaxCoordinate(body);

    Cell rootCell(position, 2 * lengthOfSpace);
    int level = 0;
    auto rootNode = std::make_unique<Node>(rootCell, position, level);

    for (size_t i = 0; i < body.size(); i++) {
        // Recursive process that add particles into the tree
        addParticle(rootNode, body, i);
    }
    return rootNode;
}

std::vector<Vector2D> BarnesHut::calculateForce() {
    // Get the tree structure
    std::unique_ptr<Node> node = buildTree();
    std::vector<Vector2D> forces(body.size());

    // Calculate forces
    for (auto iteratorToBody = body.begin(); iteratorToBody != body.end(); ++iteratorToBody) {
        size_t index = std::distance(body.begin(), iteratorToBody);
        forces[index] = calculateForceFromNode(node, iteratorToBody);
    }
    return forces;
}

void BarnesHut::addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) {
    if (node->isLeaf()) {
        if (node->getParticleIndices().empty()) {
            node->addParticleIndex(index);
            //node->setTotalMass(body[index].getWeight());
            updateMassAndCenterOfMass(node, body, index);
        } else {
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

Vector2D BarnesHut::calculateForceFromNode(std::unique_ptr<Node>& node, std::vector<Body>::const_iterator iteratorToBody) {
    if (node->isLeaf()) { 
        return calculateForceFromParticle(std::next(body.begin(), node->getParticleIndices()[0]),iteratorToBody); 
    } else {
        Vector2D force(0, 0);
        Vector2D bodyPosition = iteratorToBody->getPos();
        double bodyWeight = iteratorToBody->getWeight(); 

        for(int i = 0; i < 4; i++) {
            std::unique_ptr<Node>& child = node->getChild(static_cast<Node::Quadrant>(i));
            if (child) {
                double distance = (child->getCenterOfMass() - bodyPosition).getNorm();
                if (node->getCell().getLength() / distance < theta ) {
                    Vector2D direction = child->getCenterOfMass() - bodyPosition;
                    double magnitude = (G * child->getTotalMass() * bodyWeight) / (distance * distance);
                    force = force + direction * magnitude;
                } else {
                    force = force + calculateForceFromNode(child, iteratorToBody);
                }
            }
        }
        return force;
    }
}

Vector2D BarnesHut::calculateForceFromParticle(std::vector<Body>::const_iterator iteratorToBody1, std::vector<Body>::const_iterator iteratorToBody2) {
    Vector2D force(0, 0);

    Body particle1 = *iteratorToBody1;
    Body particle2 = *iteratorToBody2;

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

