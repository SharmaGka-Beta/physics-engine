#pragma once

#include <SFML/Graphics.hpp>
#include "universal.h"
#include <unordered_map>
#include <string>
#include "entity.h"

class Ball : public Universal, public Entity{
    private:

        sf::Vector2f position{};
        sf::Vector2f velocity{};
        sf::Vector2f acceleration{};
        sf::CircleShape obj{};
        float mass = 1.f;

    public:
        explicit Ball(float);

        void drawBall(sf::RenderWindow&);
        void setShapePosition();

        void setPosition(sf::Vector2f);
        void setVelocity(sf::Vector2f);
        void setAcceleration(sf::Vector2f);
        void setRadius(float);
        void setMass(float);
        
        void update(float);

        sf::Vector2f getPosition();
        sf::Vector2f getVelocity();
        float getRadius();
        float getMass();

        std::unordered_map <std::string, sf::Vector2f*> getPointers();
        std::unordered_map <std::string, float*> getPointersFloat();

};

Ball ballGenerator(float, sf::Vector2f, sf::Vector2f, sf::Vector2f, float);