#ifndef BARNESHUT_HPP
#define BARNESHUT_HPP

#include "Vector2D.hpp"
#include "Body.hpp"
#include "Node.hpp"
#include <vector>

class BarnesHut {
public:
    BarnesHut(const std::vector<Body>& body, float theta);
    std::unique_ptr<Node> buildTree();
    std::vector<Vector2D> calculateForce();
    Vector2D calculateBruteForce(size_t particleIndex1, size_t particleIndex2) const;
    Vector2D calculateForceFromNode(std::unique_ptr<Node>& node, std::vector<Body>::const_iterator iteratorToBody);
    Vector2D calculateForceFromParticle(std::vector<Body>::const_iterator iteratorToBody1, std::vector<Body>::const_iterator iteratorToBody2);

private:
    void addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);
    void updateMassAndCenterOfMass(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);
    double getMaxCoordinate(const std::vector<Body>& body);
   
    const std::vector<Body>& body;
    float theta;
};

#endif // BARNESHUT_HPP
