#include <gui.hpp>
#include <DataPoint.hpp>
#include <InputHandler.hpp>
#include <Body.hpp>


#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

void add(std::vector<int> &state)
{   
    state.push_back(1);
    state.push_back(2);
    state.push_back(3);
}


int main()
{
    GravityGUI gui(600, 600);

    std::vector<std::vector<DataPoint>> stateOfDataPointsOverTime;
    
    // std::vector<DataPoint> step1 = {
    //     DataPoint({}, {}, 400, 500, {}, {}, {}, {}),
    //     DataPoint({}, {}, 500, 200, {}, {}, {}, {})
    // };
    // stateOfDataPointsOverTime.push_back(step1);

    // std::vector<DataPoint> step2 = {
    //     DataPoint({}, {}, 100, 200, {}, {}, {}, {}),
    //     DataPoint({}, {}, 200, 300, {}, {}, {}, {})
    // };
    // stateOfDataPointsOverTime.push_back(step2);

    // std::vector<int> vec;
    // add(vec);
    // for (auto body : vec)
    // {
    //     std::cout << body << std::endl;
    // }

    std::vector<Body> stateOfBodies;
    InputHandler input_handler(stateOfBodies);

    // input_handler.fillStateOfBodiesRandomly(3, 10000, 1);
    // std::cout << stateOfBodies.size() << std::endl;
    // for (auto body : stateOfBodies)
    // {
    //     std::cout << body.getPos().x << std::endl;
    // }

    for (int i = 0; i < 5; i++)
    {
        input_handler.fillStateOfBodiesRandomly(10);
        std::vector<DataPoint> step;
        for (auto body : stateOfBodies)
        {
            step.push_back(DataPoint(body));
            std::cout << body.getPos().x << std::endl;
        }
        stateOfDataPointsOverTime.push_back(step);
    }

    gui.renderFromFile(stateOfDataPointsOverTime);
    return 0;
}
