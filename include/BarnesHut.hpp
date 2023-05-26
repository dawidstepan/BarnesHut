#ifndef BARNESHUT_HPP
#define BARNESHUT_HPP

#include "Node.hpp"
#include "Vector2D.hpp"

class BarnesHut {
public:
    BarnesHut(std::vector<Vector2D>& stateOfBodies, std::vector<double>& masses, double theta);

    std::unique_ptr<Node> buildTree();
    Vector2D calculateForce(const Node& node, const Vector2D& bodyPosition);
    Vector2D getForceByNaiveAlgorithm(const std::vector<Vector2D>& bodies);

private:
    std::vector<Vector2D> stateOfBodies;
    std::vector<double> masses;
    double theta;
};

#endif  // BARNESHUT_HPP
