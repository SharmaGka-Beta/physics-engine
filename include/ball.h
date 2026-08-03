#pragma once

#include <SFML/Graphics.hpp>
#include "universal.h"

inline const int PIXELS_PER_METER = 50;

class Ball : public Universal{
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        sf::CircleShape obj;
    public:
        explicit Ball(float radius);

        void drawBall(sf::RenderWindow& window);
        void setShapePosition();

        void setPosition(sf::Vector2f pos);
        void setVelocity(sf::Vector2f vel);
        void setAcceleration(sf::Vector2f acc);
        void update(float dt);

        sf::Vector2f getPosition();
        float getRadius();
};

Ball ballGenerator(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration);