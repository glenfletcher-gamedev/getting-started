#include "ball.h"
#include <cmath>
#include "vector.h"
#include "quadratic.h"
#include "ball_getstate.h"

Ball::Ball(float radius, sf::Vector2f pos0, sf::Vector2f vec0, sf::Color color) :
    radius{radius}, pos{pos0, {0.f, 0.f}, {0.f, 0.f}}, vec{ vec0, {0.f, 0.f}, {0.f, 0.f}}
{
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
}

Ball::~Ball()
{
    //dtor
}

void Ball::update(float dt, int state)
{
    pos[state] = pos[!state] + vec[!state];
    vec[state] = vec[!state];
    lastCollision = -1.f;
}

bool checkCollide(Ball &b1, Ball &b2, int state, float& ct)
{
    sf::Vector2f r1, r2, dr1, dr2, v1, v2, dv1, dv2;
    float lt = b1.getState(state, r1, dr1, v1, dv1);
    float ltt = b2.getState(state, r2, dr2, v2, dv2);
    sf::Vector2f dr0 = r1 - r2;
    sf::Vector2f dv0 = dr1 - dr2;
    if (ltt > lt) lt = ltt; // Time of last collision, this collision must be in range [lt, 1]
    float sep = (b1.radius + b2.radius);
    float c = dot(dr0, dr0) - sep*sep;
    float b = 2*dot(dr0, dv0);
    float a = dot(dv0, dv0);
    if (evaluateQuadraticRangeMin(a, b, c, lt, 1.f, ct)) {
        sf::Vector2f p1 = r1 + dr1*ct;
        sf::Vector2f p2 = r2 + dr2*ct;
        sf::Vector2f n = norm(p1 - p2);
        sf::Vector2f vn = norm(dr1 - dr2);
        float d = dot(n,vn);
        if (d < 0) return true;
        else return false;
    }
    return false;
}

void doCollide(Ball &b1, Ball &b2, int state, float t)
{
    sf::Vector2f r1, r2, dr1, dr2, v1, v2, dv1, dv2;
    float lt = b1.getState(state, r1, dr1, v1, dv1);
    float ltt = b2.getState(state, r2, dr2, v2, dv2);
    if (ltt > lt) lt = ltt; // Time of last collision, this collision must be in range [lt, 1]
    sf::Vector2f p1 = r1 + dr1*t;
    sf::Vector2f p2 = r2 + dr2*t;
    sf::Vector2f pv1 = v1 + dv1*t;
    sf::Vector2f pv2 = v2 + dv2*t;
    sf::Vector2f n = norm(p1 - p2);
    sf::Vector2f Jr = dot(dr1 - dr2, n)*n;
    sf::Vector2f J = dot(pv1 - pv2, n)*n;
    b1.pos[state] -= (1-t)*Jr;
    b2.pos[state] += (1-t)*Jr;
    b1.vec[state] -= J;
    b2.vec[state] += J;
    b1.lastCollision = t;
    b1.pos[2] = p1;
    b1.vec[2] = pv1;
    b2.lastCollision = t;
    b2.pos[2] = p2;
    b2.vec[2] = pv2;
}

void Ball::draw(sf::RenderTarget& canvas, float alpha, int state)
{
    shape.setPosition(pos[!state]*(1-alpha) + pos[state]*alpha);
    canvas.draw(shape);
}
