#ifndef GETTINGSTARTED_H
#define GETTINGSTARTED_H

#include <Game.h>
#include "ball.h"
#include "barrier.h"

class GettingStarted : public Game
{

    private:
        bool onInit();
        void onExit();
        void onEvent(sf::Event &e);
        void onUpdate(float dt);
        void onDraw(sf::RenderTarget &canvas, float alpha);

        Ball *balls[2];
        Barrier *edges[4];
        int S = 1;
};

#endif // GETTINGSTARTED_H
