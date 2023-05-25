#pragma once

#include <SFML/Graphics.hpp>
# include "DataPoint.hpp"

struct GravityGUI {

public:
    sf::RenderWindow window;

    GravityGUI(int width, int height);

    void renderFromFile(std::vector<std::vector<DataPoint>> &stateOfDataPointsOverTime);
};