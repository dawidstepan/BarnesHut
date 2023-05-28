# include <cstdlib>
# include <ctime>

# include "InputHandler.hpp"
# include "Body.hpp"
# include "Vector2D.hpp"

void InputHandler::addToStateOfBodies(int size, double weight, Vector2D pos, Vector2D vel, Vector2D acc) {
    Body newBody(size, weight, pos, vel, acc);
    stateOfBodies.push_back(newBody);
}

// yet to be implemented
void InputHandler::parseFile() {}

void InputHandler::fillStateOfBodiesRandomly(int n, int size, double weight) {
    // Set seed value based on current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for(int m = 0; m<n; m++){
        long double x = (std::rand() % 100)*0.1; //in astronomical units (1AU ~ 1.4e8 km)
        long double y = (std::rand() % 100)*0.1;
        Vector2D pos(x, y);
        Vector2D vel(0, 0);
        Vector2D acc(0, 0);
        addToStateOfBodies(size, weight, pos, vel, acc);
    }
};


