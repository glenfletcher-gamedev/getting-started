#ifndef BALL_GETSTATE_H_INCLUDED
#define BALL_GETSTATE_H_INCLUDED

inline float Ball::getState(int state, sf::Vector2f &r, sf::Vector2f &dr, sf::Vector2f &v, sf::Vector2f &dv)
{
    float t = 0;
    if (lastCollision >= 0) {
        t = lastCollision;
        float factor = 1.f/(1.f - t);
        sf::Vector2f drt = pos[state] - pos[2];
        dr = drt*factor;
        r = pos[2] - dr*t;
        sf::Vector2f dvt = vec[state] - vec[2];
        dv = dvt*factor;
        v = vec[2] - dv*t;
    } else {
        r = pos[!state];
        dr = pos[state] - pos[!state];
        v = vec[!state];
        dv = vec[state] - vec[!state];
    }
    return t;
}

#endif // BALL_GETSTATE_H_INCLUDED
