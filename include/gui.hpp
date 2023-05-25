#pragma once

#include <SFML/Graphics.hpp>
# include "DataPoint.hpp"


/************************************************
 * Class holding the SFML window and handling the rendering.
 ***********************************************/
struct GravityGUI {

public:
    sf::RenderWindow window;

    GravityGUI(int width);

    /************************************************
     * Method to run an animation from a trajectory of a gravity simulation.
     * The trajectory is passed in form of a vector std::vector<std::vector<DataPoint>>
     * which has shape (T, N), where T is the number of saved timesteps and N is the 
     * number of Bodies. Assuming N=const for now.
     * 
     * Disclaimer:
     * This is not working at the moment!
     ***********************************************/
    void renderTrajectory(std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime);

    /************************************************
     * Method to render only one snapshot of a simulation, corresponding to a single
     * timestep for example.
     ***********************************************/
    void renderSnapshot(std::vector<DataPoint> &stateOfDataPoints);

};