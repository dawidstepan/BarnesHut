# include <cstdlib>
# include <ctime>
# include <random>

# include "InputHandler.hpp"
# include "Body.hpp"
# include "Vector2D.hpp"

void InputHandler::addToStateOfBodies(int size, double weight, Vector2D pos, Vector2D vel, Vector2D acc) {
    Body newBody(size, weight, pos, vel, acc);
    stateOfBodies.push_back(newBody);
}

// yet to be implemented
void InputHandler::parseFile() {}

void InputHandler::fillStateOfBodiesRandomly(int n, int size, double weight, Vector2D origin, Vector2D scale) {
    // Set seed value based on current time
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform real distribution in the range [0, 1]
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    // Generate a random float value
    float randomValue = dist(gen);

    for(int m = 0; m<n; m++){
        long double x = dist(gen) * scale.x + origin.x; //in astronomical units (1AU ~ 1.4e8 km)
        long double y = dist(gen) * scale.y + origin.y;
        Vector2D pos(x, y);
        Vector2D vel(0, 0);
        Vector2D acc(0, 0);
        addToStateOfBodies(size, weight, pos, vel, acc);
    }
};


