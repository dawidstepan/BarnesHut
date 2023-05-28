#ifndef GROUPMPROJECT_INPUTHANDLER_HPP
#define GROUPMPROJECT_INPUTHANDLER_HPP

#include <vector>
#include "Body.hpp"
#include "Vector2D.hpp"

/** \brief responsible for filling up stateOfBodies
 *
 * has to be initialized with pointer to stateOfBodies, like this:
 * \code{.cpp}
 * std::vector<Body> stateOfBodies;
 * InputHandler newInputHandler(&stateOfBodies);
 * \endcode
 */
class InputHandler {
public:
    /// initializer list used to initialize our "local" version of stateOfBodies with the one we got passed over as a pointer
    InputHandler(std::vector<Body> &stateOfBodies): stateOfBodies(stateOfBodies){};
    // InputHandler(){};
    /// creats Body object based on intput and adds it ot stateOfBodies
    void addToStateOfBodies(int size, double weight, Vector2D pos, Vector2D vel, Vector2D acc);

    /// reads in a user provided txt file and calls addToStateOfBodies for every relevant line
    void parseFile();

    /// creates n-bodies, randomly distributed over 10AU^2 (AU = astronomical unit)
    /// default values correspond roughly to size and mass of our sun
    void fillStateOfBodiesRandomly(int n,int size = 696340, double weight  = 1);

private:
    std::vector<Body> &stateOfBodies;
};

#endif //GROUPMPROJECT_INPUTHANDLER_HPP
