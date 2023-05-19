#ifndef GROUPMPROJECT_NAIVEALGORITHM_HPP
#define GROUPMPROJECT_NAIVEALGORITHM_HPP


#include <vector>
#include "Vector2D.hpp"
#include "Body.hpp"

class NaiveAlgorithm {
public:
    std::vector<Vector2D> runAlgorithm(std::vector<Body> currentStateOfBodies);
};


#endif //GROUPMPROJECT_NAIVEALGORITHM_HPP
