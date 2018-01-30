#ifndef VECTOR_H
#define VECTOR_H

#include <SFML/Graphics.hpp>
#include <cmath>

template<typename T>
inline constexpr T dot(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
inline constexpr T abs(const sf::Vector2<T> &v)
{
    return sqrt(dot(v, v));
}

template<typename T>
inline constexpr sf::Vector2<T> norm(const sf::Vector2<T> &v)
{
    return v/abs(v);
}


#endif // VECTOR_H
