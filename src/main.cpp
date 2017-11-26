#include <SFML/Graphics.hpp>

const sf::Vector2i size = {800, 600};
const float radius = 10.0f;

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "First SFML Program");
    window.setVerticalSyncEnabled(true);
    sf::Transform rotation;
    sf::CircleShape shape(radius);
    sf::Vector2f pos(size.x/2.0f - radius,size.y/2.0f - radius);
    sf::Vector2f vec(5, 5);
    rotation.rotate(1.5);
    shape.setFillColor(sf::Color::Blue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        shape.setPosition(pos);
        if (pos.x <= 0 and vec.x < 0 or pos.x >= size.x - 2*radius and vec.x > 0) vec.x = -vec.x;
        if (pos.y <= 0 and vec.y < 0 or pos.y >= size.y - 2*radius and vec.y > 0) vec.y = -vec.y;
        pos += vec;
        vec = rotation.transformPoint(vec);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}
