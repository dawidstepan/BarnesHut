# include <iostream>
# include "InputHandler.hpp"
# include "Body.hpp"
# include "Vector2D.hpp"

void InputHandler::addToStateOfBodies(int size, int weight, Vector2D pos, Vector2D vel, Vector2D acc) {
    Body newBody(size, weight, pos, vel, acc);
    stateOfBodies -> push_back(newBody);
    std::cout << "new Body added!" << std::endl;
}

// yet to be implemented
void InputHandler::parseFile() {}

//yet to be implemented
void InputHandler::fillStateOdBodiesRandomly(int n, int size, int weight) {};


