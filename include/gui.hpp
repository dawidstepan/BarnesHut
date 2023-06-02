#pragma once

#include <SFML/Graphics.hpp>

#include "Simulation.hpp"
#include "DataPoint.hpp"
#include "RenderTargets.hpp"
#include <Widgets.hpp>


/************************************************
 * Class holding the SFML window and handling the rendering.
 ***********************************************/
struct GravityGUI {

private:
    sf::RenderWindow window;
    std::shared_ptr<Transformation> transformation;
    int print_fps_every;

public:
    /************************************************
     * @brief Constructs a GravityGUI object with the specified width and transform.
     *
     * This constructor initializes a GravityGUI object with the given width and transform.
     * It creates a graphical user interface for a gravity simulation. 
     *
     * @param width The width of the GUI window.
     * @param transform The type of transformation to apply.
     *                  This can be one of the following:
     *                  - "Rescale": Linear rescaling transformation.
     *                  - "Identity": Identity transformation (no transformation).
     * @param range The range of values for the transformation.
     *              The range should contain two elements: the minimum and maximum value.
     *              
     ***********************************************/
    GravityGUI(int width, std::string transform = "Rescale", 
               std::vector<float> range = {0.f, 10.f},
               int print_fps_every = 10);

    /************************************************
     * Method to run an animation from a trajectory of a gravity simulation.
     * The trajectory is passed in form of a vector std::vector<std::vector<DataPoint>>
     * which has shape (T, N), where T is the number of saved timesteps and N is the 
     * number of Bodies. Assuming N=const for now.
     ***********************************************/
    void renderTrajectory(std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime);

    /************************************************
     * Method to render only one snapshot of a simulation, corresponding to a single
     * timestep for example.
     ***********************************************/
    void renderSnapshot(std::vector<DataPoint> &stateOfDataPoints);

    void renderSimulation(Simulation &simulation);

};