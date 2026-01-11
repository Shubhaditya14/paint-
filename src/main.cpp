#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    // SFML 3.0.0 uses sf::Vector2u for VideoMode size
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3.0.0 - Paint");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin({100.f, 100.f});
    shape.setPosition({400.f, 300.f});

    while (window.isOpen())
    {
        // SFML 3.0.0 event polling returns std::optional<sf::Event>
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}