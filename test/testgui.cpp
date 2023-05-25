#include <gui.hpp>
#include <DataPoint.hpp>
#include <InputHandler.hpp>
#include <Body.hpp>
#include <RenderTargets.hpp>


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int main()
{
    GravityGUI gui(600);

    std::vector<std::vector<DataPoint>> stateOfDataPointsOverTime;

    std::vector<Body> stateOfBodies;
    InputHandler input_handler(stateOfBodies);

    for (int i = 0; i < 100; i++)
    {
        input_handler.fillStateOfBodiesRandomly(100);
        std::vector<DataPoint> step;
        for (auto body : stateOfBodies)
        {
            step.push_back(DataPoint(body));
        }
        stateOfDataPointsOverTime.push_back(step);
    }

    std::cout << stateOfDataPointsOverTime.size() << std::endl;
    std::cout << stateOfDataPointsOverTime[0].size() << std::endl;

    // Rendering the first Snapshot from the artificial trajectory
    gui.renderSnapshot(stateOfDataPointsOverTime[10]);

    // Rendering The artificial trajectory doesnt work for some reason
    // Getting a Segfault..
    // gui.renderTrajectory(stateOfDataPointsOverTime);
    return 0;
}
