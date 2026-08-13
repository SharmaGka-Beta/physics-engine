#pragma once

#include <SFML/Graphics.hpp>


class Universal{
    private:

        static sf::Vector2f velocityUniversal;
        static sf::Vector2f accelerationUniversal;

    public:

        static void setVelocityUniversal(sf::Vector2f);
        static void setAccelerationUniversal(sf::Vector2f);
        sf::Vector2f getVelocityUniversal();
        sf::Vector2f getAccelerationUniversal();
};