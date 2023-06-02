#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Input Field");
    sf::Font font;
    if (!font.loadFromFile("../assets/DejaVuSerif.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    std::string inputText;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == '\b' && !inputText.empty())
                    {
                        // Backspace: remove the last character
                        inputText.pop_back();
                    }
                    else if (event.text.unicode == '\r')
                    {
                        // Enter/Return: process the input text
                        std::cout << "Input: " << inputText << std::endl;
                        inputText.clear();
                    }
                    else if (event.text.unicode >= 32)
                    {
                        // Valid character: append to the input text
                        inputText += static_cast<char>(event.text.unicode);
                    }

                    // Update the displayed text
                    text.setString(inputText);
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }

    return 0;
}
