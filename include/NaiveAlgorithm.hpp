#ifndef GROUPMPROJECT_NAIVEALGORITHM_HPP
#define GROUPMPROJECT_NAIVEALGORITHM_HPP


#include <vector>
#include "Vector2D.hpp"
#include "Body.hpp"

class NaiveAlgorithm {
public:
    std::vector<Vector2D> calculateForce(std::vector<Body> currentStateOfBodies);
};


#endif //GROUPMPROJECT_NAIVEALGORITHM_HPP
