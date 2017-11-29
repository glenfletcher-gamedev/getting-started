#include "gettingstarted.h"

AGL_IMPLIEMENT_GAME(GettingStarted)

const sf::Vector2i size = {800, 600};
const float radius = 10.f;
const float FPS = 300.0f;
const float refresh = 5.0f;

bool GettingStarted::onInit() {
    setSize(size);
    setTitle("First SFML Program");
    setFPS(FPS);
    setRefresh(refresh);
    shape = sf::CircleShape{radius};
    pos[0] = {size.x/2.0f - radius, size.y/2.0f - radius};
    pos[1] = {0,0};
    vec[0] = {300, 300};
    vec[1] = {0, 0};
    shape.setFillColor(sf::Color::Blue);
    rotation.rotate(90/FPS);
    return true;
}

void GettingStarted::onEvent(sf::Event &e) {
}

void GettingStarted::onUpdate(float dt) {
    pos[S] = pos[!S] + vec[!S]*dt;
    vec[S] = rotation.transformPoint(vec[!S]);
    if (pos[S].x <= 0 and vec[S].x < 0 or pos[S].x >= size.x - 2*radius and vec[S].x > 0) vec[S].x = -vec[S].x;
    if (pos[S].y <= 0 and vec[S].y < 0 or pos[S].y >= size.y - 2*radius and vec[S].y > 0) vec[S].y = -vec[S].y;
    S = !S;
}

void GettingStarted::onDraw(sf::RenderTarget &canvas, float alpha) {
    shape.setPosition(pos[!S]*(1-alpha) + pos[S]*alpha);
    canvas.draw(shape);
}
