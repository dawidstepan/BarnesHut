#include <gui.hpp>
#include <RenderTargets.hpp>
#include <Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include <stdexcept>
#include <cmath>


ProgressBar::ProgressBar(sf::RenderWindow &window)
: window(window)
{   
    bar_width = 0.8 * window.getSize().x;
    bar_height = 10.f;
    sf::Vector2f barsize(bar_width, bar_height);
    outer_hull.setSize(barsize);
    outer_hull.setFillColor(sf::Color::White);
    outer_hull.setOutlineColor(sf::Color::Blue);
    outer_hull.setOutlineThickness(2.f);
    auto outer_pos = sf::Vector2f(0.1 * window.getSize().x, 0.9 * window.getSize().y);
    outer_hull.setPosition(outer_pos);

    progress_bar.setPosition(outer_pos);
    progress_bar.setFillColor(sf::Color::Blue);
}

void ProgressBar::draw(float progress)
{   
    progress_bar.setSize(sf::Vector2f(progress * bar_width, bar_height));
    window.draw(outer_hull);
    window.draw(progress_bar);
}


FPSDisplay::FPSDisplay(sf::RenderWindow &window, int font_size)
: window(window)
{
    font.loadFromFile("../assets/DejaVuSerif.ttf");
    text.setFont(font);
    text.setCharacterSize(font_size);
    text.setFillColor(sf::Color::Red);
    text.setPosition(sf::Vector2f(0.01 * window.getSize().x, 0.01 * window.getSize().y));
}

void FPSDisplay::draw(int frames_per_second)
{  
    std::string str = "FPS: " + std::to_string(frames_per_second);
    text.setString(str);
    window.draw(text);
}




Button::Button(const sf::Vector2f position, const std::string text_on,
               const std::string text_off, sf::RenderWindow &window)
: window(window), text_on(text_on), text_off(text_off)
{
    shape.setPosition(position);
    shape.setSize(sf::Vector2f(150, 50)); // Adjust the size as needed
    shape.setFillColor(color_off); // Adjust the color as needed

    font.loadFromFile("../assets/DejaVuSerif.ttf");
    label.setString(text_off);
    label.setFont(font);
    label.setCharacterSize(24); // Adjust the font size as needed
    label.setFillColor(sf::Color::White); // Adjust the text color as needed

    // Center the text within the button
    sf::FloatRect labelBounds = label.getLocalBounds();
    center_text();
}

void Button::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        if (shape.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            pressed = !pressed;
            if (pressed){
                shape.setFillColor(color_on);
                label.setString(text_on);
                center_text();
                label.setFillColor(sf::Color::Black);
            }
            else {
                shape.setFillColor(color_off);
                label.setString(text_off);
                center_text();
                label.setFillColor(sf::Color::White);
            }
            window.draw(shape);
            window.draw(label);
        }
    }
}

void Button::draw() {
    window.draw(shape);
    window.draw(label);
}

bool Button::isPressed() {
    return pressed;
}

void Button::center_text() {
    sf::FloatRect textBounds = label.getLocalBounds();
    auto position = shape.getPosition();
    auto size = shape.getSize();
    label.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    label.setPosition(position.x + size.x / 2.f, position.y + size.y / 2.f);
}