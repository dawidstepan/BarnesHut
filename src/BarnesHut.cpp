#include "BarnesHut.hpp"

BarnesHut::BarnesHut(std::vector<Vector2D>& stateOfBodies, std::vector<double>& masses, double theta) 
    : stateOfBodies(stateOfBodies), masses(masses), theta(theta) {
    // Implement constructor as needed
}

std::unique_ptr<Node> BarnesHut::buildTree() {
    // Implement the Barnes Hut tree algorithm and return the root of the tree
}

Vector2D BarnesHut::calculateForce(const Node& node, const Vector2D& bodyPosition) {
    // Implement the force calculation algorithm using the tree 
}

Vector2D BarnesHut::getForceByNaiveAlgorithm(const std::vector<Vector2D>& bodies) {
    // Implement the naive force calculation algorithm 
}