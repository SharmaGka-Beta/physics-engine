#pragma once

#include <SFML/Graphics.hpp>

inline const int PIXELS_PER_METER = 50;

class Ball{
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
};

Ball ballGenerator(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration);