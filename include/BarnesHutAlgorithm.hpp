#ifndef GROUPMPROJECT_BARNESHUTALGORITHM_HPP
#define GROUPMPROJECT_BARNESHUTALGORITHM_HPP

#include <vector>
#include "Vector2D.hpp"
#include "Body.hpp"

class BarnesHutAlgorithm{
public:
    std::vector<Vector2D> calculateForce(std::vector<Body> currentStateOfBodies);
};
#endif //GROUPMPROJECT_BARNESHUTALGORITHM_HPP
