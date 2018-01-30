#ifndef BALL_H
#define BALL_H

#include <Game.h>

class Barrier;

class Ball
{
    friend bool checkCollide(Ball &b1, Ball &b2, int state, float &t);
    friend void doCollide(Ball &b1, Ball &b2, int state, float t);

    friend bool checkCollide(Ball &b1, Barrier &b2, int state, float &t);
    friend void doCollide(Ball &b1, Barrier &b2, int state, float t);

    friend bool checkCollide(Barrier &b1, Ball &b2, int state, float &t);
    friend void doCollide(Barrier &b1, Ball &b2, int state, float t);

    public:
        /** Default constructor */
        Ball(float radius, sf::Vector2f pos, sf::Vector2f vec, sf::Color color);
        /** Default destructor */
        virtual ~Ball();

        void update(float dt, int state);
        void draw(sf::RenderTarget &canvas, float alpha, int state);
    protected:

    private:
        float getState(int state, sf::Vector2f &r, sf::Vector2f &dr, sf::Vector2f &v, sf::Vector2f &dv);
        sf::CircleShape shape;
        float radius;
        float lastCollision = 0;
        sf::Vector2f pos[3]; // [state0, state1, lastCollision]
        sf::Vector2f vec[3];
};

#endif // BALL_H
