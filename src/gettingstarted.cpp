#include "gettingstarted.h"

AGL_IMPLIEMENT_GAME(GettingStarted)

const sf::Vector2i size = {800, 600};
const float radius = 10.f;
const float FPS = 30.0f;
const float refresh = 5.0f;

bool GettingStarted::onInit() {
    setSize(size);
    setTitle("First SFML Program");
    setFPS(FPS);
    setRefresh(refresh);
    balls[0] = new Ball{radius, {size.x/3.0f - radius, size.y/2.0f - radius}, {10, 10}, sf::Color::Blue};
    balls[1] = new Ball{radius, {2*size.x/3.0f - radius, size.y/2.0f - radius}, {-10, 10}, sf::Color::Green};
    edges[0] = new Barrier{{1,0}, 0};
    edges[1] = new Barrier{{0,1}, 0};
    edges[2] = new Barrier{{1,0}, size.x};
    edges[3] = new Barrier{{0,1}, size.y};
    return true;
}

void GettingStarted::onExit() {
    delete balls[0];
    delete balls[1];
    delete edges[0];
    delete edges[1];
    delete edges[2];
    delete edges[3];
}

void GettingStarted::onEvent(sf::Event &e) {
}

enum class CollisionType { None, BallBall, BallBarier };

struct Collision {
    CollisionType type = CollisionType::None;
    int objects[2] = {0, 0};
    float time = 0.0f;
};

void GettingStarted::onUpdate(float dt) {
    balls[0]->update(dt, S);
    balls[1]->update(dt, S);
    Collision nextCollision;
    float ct;
    while (true) {
        if (checkCollide(*balls[0], *balls[1], S, ct)) {
            nextCollision.type = CollisionType::BallBall;
            nextCollision.objects[0] = 0;
            nextCollision.objects[1] = 1;
            nextCollision.time = ct;
        } else {
            nextCollision.type = CollisionType::None;
        }
        for (int i=0;i<2;i++) {
            for (int j=0;j<4;j++) {
                if (checkCollide(*balls[i], *edges[j], S, ct) and (nextCollision.time >= ct or nextCollision.type == CollisionType::None)) {
                    nextCollision.type = CollisionType::BallBarier;
                    nextCollision.objects[0] = i;
                    nextCollision.objects[1] = j;
                    nextCollision.time = ct;
                }
            }
        }
        if (nextCollision.type == CollisionType::None) {
            break; // No New collision
        } else {
            if (nextCollision.type == CollisionType::BallBall) {
                doCollide(*balls[nextCollision.objects[0]], *balls[nextCollision.objects[1]], S, nextCollision.time);
            } else {
                doCollide(*edges[nextCollision.objects[1]], *balls[nextCollision.objects[0]], S, nextCollision.time);
            }
        }
    }
    S = !S; // flip state
}

void GettingStarted::onDraw(sf::RenderTarget &canvas, float alpha) {
    balls[0]->draw(canvas, alpha, S);
    balls[1]->draw(canvas, alpha, S);
}
