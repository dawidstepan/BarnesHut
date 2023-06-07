#include "BarnesHut.hpp"
#include "Vector2D.hpp"
#include "Body.hpp"
#include "testasserts.hpp"
#include "Cell.hpp"
#include "Node.hpp"
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <vector>

template <typename BodyType>
void runBarnesHutForceCalculationTest(size_t numParticles, double lengthOfSpace, double epsilon) {
    const double theta = 0.0;
    std::vector<BodyType> body;

    // Generate random objects
    for (size_t i = 0; i < numParticles; ++i) {
        double x = (static_cast<double>(rand()) / RAND_MAX) * 2 * lengthOfSpace - lengthOfSpace;
        double y = (static_cast<double>(rand()) / RAND_MAX) * 2 * lengthOfSpace - lengthOfSpace;
        Vector2D pos(x, y);
        double mass = static_cast<double>(rand()) / RAND_MAX * lengthOfSpace;
        body.push_back(BodyType(0, mass, pos, Vector2D(0, 0), Vector2D(0, 0)));
    }

    // Initialize Barnes-Hut
    BarnesHut barneshut(body, theta, lengthOfSpace);

    // Calculate forces using Barnes-Hut
    std::vector<Vector2D> forcesBarnesHut = barneshut.calculateForce();

    // Calculate forces using brute force method (direct summation method)
    std::vector<Vector2D> forcesBruteForce(numParticles);
    for (size_t i = 0; i < numParticles; i++) {
        for (size_t j = 0; j < numParticles; j++) {
            if (i != j) {
                forcesBruteForce[i] = forcesBruteForce[i] + barneshut.calculateBruteForce(j, i);
            }
        }
    }

    // Compare the two force calculations
    for (size_t i = 0; i < numParticles; ++i) {
        Vector2D diff = forcesBarnesHut[i] - forcesBruteForce[i];
        double error = diff.getNorm() / forcesBruteForce[i].getNorm();
        TEST_ASSERT(error < epsilon, "The forces calculation of the Barnes-Hut algorithm with theta = 0 are at least for one particle not equal to the brute force method! \nPlease check the calculation!");
    }
}

int main() {
    size_t numParticles = 1000;
    double lengthOfSpace = 10.0;
    double epsilon = 1.0e-12;

    // Test setzen wenn fertig!
    //runBarnesHutForceCalculationTest<Body>(numParticles, lengthOfSpace, epsilon);

    return 0;
}