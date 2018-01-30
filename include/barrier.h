#ifndef BARRIER_H
#define BARRIER_H

#include <Game.h>

class Ball;

class Barrier
{
    friend bool checkCollide(Ball &b1, Barrier &b2, int state, float &t);
    friend void doCollide(Ball &b1, Barrier &b2, int state, float t);

    friend bool checkCollide(Barrier &b1, Ball &b2, int state, float &t);
    friend void doCollide(Barrier &b1, Ball &b2, int state, float t);

    public:
        /** Default constructor */
        Barrier(sf::Vector2f normal, float alpha);
        Barrier(sf::Vector2f normal, sf::Vector2f point) : Barrier{normal, -(normal.x*point.x + normal.y*point.y)} {};
        /** Default destructor */
        virtual ~Barrier();

    protected:

    private:
        sf::Vector2f normal;
        float alpha;
};

#endif // BARRIER_H
