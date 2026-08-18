#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>

class Wall : public Entity{

    private:
        sf::RectangleShape rec{};
        sf::Vector2f position{};

    public:
        explicit Wall(sf::Vector2f);

        void drawWall(sf::RenderWindow&);
        void setShapePosition();
        void setPosition(sf::Vector2f);
        void setDimensions(sf::Vector2f);
};