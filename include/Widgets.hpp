#pragma once

#include <SFML/Graphics.hpp>
#include "DataPoint.hpp"
#include "RenderTargets.hpp"


/**
 * @brief The FPSDisplay class represents a frames per second (FPS) display.
 *
 * It displays the current FPS on the SFML window.
 */
struct FPSDisplay {
    /**
     * @brief Construct a new FPSDisplay object.
     *
     * @param window The SFML RenderWindow to display the FPS on.
     * @param font_size The size of the font used for displaying the FPS. Default is 24.
     */
    FPSDisplay(sf::RenderWindow& window, int font_size = 24);

    /**
     * @brief Draw the FPS on the SFML window.
     *
     * @param frames_per_second The current frames per second value to display.
     */
    void draw(int frames_per_second);

private:
    sf::Font font;
    sf::Text text;
    sf::RenderWindow &window;

};


/**
 * @brief The ProgressBar class represents a progress bar.
 *
 * It draws a progress bar on the SFML window.
 */
struct ProgressBar {
    /**
     * @brief Construct a new ProgressBar object.
     *
     * @param window The SFML RenderWindow to draw the progress bar on.
     */
    ProgressBar(sf::RenderWindow& window);

    /**
     * @brief Draw the progress bar on the SFML window.
     *
     * @param progress The progress value, ranging from 0.0 to 1.0, to represent the filled portion of the progress bar.
     */
    void draw(float progress);

private:
    sf::RectangleShape outer_hull;
    sf::RectangleShape progress_bar;
    float bar_width;
    float bar_height;
    sf::RenderWindow &window;
};




struct Button {
    sf::RectangleShape shape;
    sf::Text label;
    std::string text_on;
    std::string text_off;
    bool pressed = false;
    sf::RenderWindow &window;
    sf::Color color_off = sf::Color::Green;
    sf::Color color_on = sf::Color::White;
    sf::Font font;

    Button(const sf::Vector2f position, const std::string text_on, 
           const std::string text_off, sf::RenderWindow &window);

    void handleEvent(const sf::Event& event);

    void draw();

    bool isPressed();

    void center_text();
};