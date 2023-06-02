#ifndef BARNESHUT_HPP
#define BARNESHUT_HPP

#include "Vector2D.hpp"
#include "Body.hpp"
#include "Node.hpp"
#include "BarnesHut.hpp"
#include <vector>

class BarnesHut {
public:
    BarnesHut(const std::vector<Body>& body, double theta, double lengthOfSpace);
    std::unique_ptr<Node> buildTree(const std::vector<Body>& body, double lengthOfSpace);
    Vector2D calculateForce(const Node& node, const Vector2D& bodyPosition);
    Vector2D getForceByNaiveAlgorithm(const std::vector<Vector2D>& bodies);

private:
    void addParticle(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);
    void updateMassAndCenterOfMass(std::unique_ptr<Node>& node, const std::vector<Body>& body, size_t index);

    const std::vector<Body>& body;
    double theta;
    double lengthOfSpace;
};
#endif  // BARNESHUT_HPP