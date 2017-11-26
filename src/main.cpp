#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "First SFML Program");
    sf::CircleShape shape(10.0f);
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(400,250);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}
