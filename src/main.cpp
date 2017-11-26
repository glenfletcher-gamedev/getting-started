#include <SFML/Graphics.hpp>

const sf::Vector2i size = {800, 600};
const float radius = 10.f;
const float FPS = 300.0f;
const float dt = 1.f/FPS; // compute time step
const float refresh = 5c.0f;

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "First SFML Program");
    sf::CircleShape shape(radius);
    sf::Transform rotation;
    sf::Vector2f pos[2] = {{size.x/2.0f - radius,size.y/2.0f - radius}, {0,0}};
    sf::Vector2f vec[2] = {{300, 300}, {0, 0}};
    sf::Clock clock;
    float remaining = 0;
    int S = 1;

    window.setVerticalSyncEnabled(true);
    shape.setFillColor(sf::Color::Blue);
    rotation.rotate(90*dt);

    while (window.isOpen())
    {
        sf::Time eps = clock.restart();
        remaining += eps.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (remaining*refresh > 1.f) return EXIT_FAILURE;

        while (remaining >= dt) {
            pos[S] = pos[!S] + vec[!S]*dt;
            vec[S] = rotation.transformPoint(vec[!S]);
            if (pos[S].x <= 0 and vec[S].x < 0 or pos[S].x >= size.x - 2*radius and vec[S].x > 0) vec[S].x = -vec[S].x;
            if (pos[S].y <= 0 and vec[S].y < 0 or pos[S].y >= size.y - 2*radius and vec[S].y > 0) vec[S].y = -vec[S].y;
            S = !S;
            remaining -= dt;
        }

        alpha = remaining*FPS;
        window.clear();
        shape.setPosition(pos[!S]*(1-alpha) + pos[S]*alpha);
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}
