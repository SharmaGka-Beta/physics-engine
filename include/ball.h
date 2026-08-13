#pragma once

#include <SFML/Graphics.hpp>
#include "universal.h"
#include <unordered_map>
#include <string>

class Ball : public Universal{
    private:
        sf::Vector2f position{};
        sf::Vector2f velocity{};
        sf::Vector2f acceleration{};
        sf::CircleShape obj{};
    public:
        explicit Ball(float);

        void drawBall(sf::RenderWindow&);
        void setShapePosition();

        void setPosition(sf::Vector2f);
        void setVelocity(sf::Vector2f);
        void setAcceleration(sf::Vector2f);
        void setRadius(float);
        void update(float);

        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        
        float getRadius();

        std::unordered_map <std::string, sf::Vector2f*> getPointers();
};

Ball ballGenerator(float, sf::Vector2f, sf::Vector2f, sf::Vector2f);