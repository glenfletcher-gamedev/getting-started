#ifndef GETTINGSTARTED_H
#define GETTINGSTARTED_H

#include <Game.h>


class GettingStarted : public Game
{
    private:
        bool onInit();
        void onEvent(sf::Event &e);
        void onUpdate(float dt);
        void onDraw(sf::RenderTarget &canvas, float alpha);

        sf::CircleShape shape;
        sf::Transform rotation;
        sf::Vector2f pos[2];
        sf::Vector2f vec[2];
        int S = 1;
};

#endif // GETTINGSTARTED_H
