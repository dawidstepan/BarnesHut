#ifndef BARNESHUT_HPP
#define BARNESHUT_HPP

#include "Vector2D.hpp"
#include "Body.hpp"
#include "Node.hpp"
#include <vector>

class BarnesHut {
public:
    BarnesHut(const std::vector<Body>& body, double theta, double lengthOfSpace);
    std::unique_ptr<Node> buildTree();
    std::vector<Vector2D> calculateForce();
    Vector2D calculateBruteForce(size_t particleIndex1, size_t particleIndex2) const;

private:
    void addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);
    void updateMassAndCenterOfMass(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);
    //Vector2D calculateForceFromNode(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index) const;
    //Vector2D calculateForceFromParticle(const std::vector<Body>& body, size_t index1, size_t index2) const;

    const std::vector<Body>& body;
    double theta;
    double lengthOfSpace;
};

#endif // BARNESHUT_HPP
