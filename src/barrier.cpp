#include "barrier.h"
#include "ball.h"
#include "vector.h"
#include "quadratic.h"
#include "ball_getstate.h"

Barrier::Barrier(sf::Vector2f normal, float alpha) :
    normal{norm(normal)}, alpha{alpha}
{
    //ctor
}

Barrier::~Barrier()
{
    //dtor
}


bool checkCollide(Ball &b1, Barrier &b2, int state, float &t)
{
    return checkCollide(b2, b1, state, t);
}

inline bool checkCollide(Barrier &b1, Ball &b2, int state, float &ct)
{
    sf::Vector2f r0, dr, v0, dv;
    float lt = b2.getState(state, r0, dr, v0, dv);
    sf::Vector2f n = norm(b1.normal);
    float Rn2 = b2.radius*b2.radius;
    float ndr = dot(n, dr);
    float nr0 = dot(n, r0);
    float a = ndr*ndr;
    float b = 2*(nr0 - b1.alpha)*ndr;
    float c = b1.alpha*b1.alpha - Rn2+(nr0-2*b1.alpha)*nr0;
    if (evaluateQuadraticRangeMin(a, b, c, lt, 1.f, ct)) {
        float Nf = dot(b1.normal, r0)-b1.alpha;
        sf::Vector2f Nv = b1.normal*Nf;
        sf::Vector2f rn = norm(Nv);
        sf::Vector2f vn = norm(dr);
        float d = dot(rn,vn);
        if (d < 0) return true;
        else return false;
    }
    return false;
}

void doCollide(Ball &b1, Barrier &b2, int state, float t)
{
    return doCollide(b2, b1, state, t);
}

inline void doCollide(Barrier &b1, Ball &b2, int state, float t)
{
    sf::Vector2f r0, dr, v0, dv;
    b2.getState(state, r0, dr, v0, dv);
    sf::Vector2f pt = r0 + dr*t;
    sf::Vector2f pvt = v0 + dv*t;
    float Nf = dot(b1.normal, r0)-b1.alpha;
    sf::Vector2f Nv = b1.normal*Nf;
    sf::Vector2f n = norm(Nv);
    sf::Vector2f Jr = 2*dot(dr, n)*n;
    sf::Vector2f J = 2*dot(pvt, n)*n;
    b2.pos[state] -= (1-t)*Jr;
    b2.vec[state] -= J;
    b2.lastCollision = t;
    b2.pos[2] = pt;
    b2.vec[2] = pvt;
}
