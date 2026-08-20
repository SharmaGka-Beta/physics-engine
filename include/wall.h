#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>

class Wall : public Entity{

    private:
        sf::RectangleShape rec{};

    public:
        explicit Wall(sf::Vector2f);
        Wall(const Wall& other);

        std::unique_ptr<Entity> clone() const override;


        void setDimensions(sf::Vector2f);
        sf::Vector2f getDimensions();

};

std::unique_ptr<Wall> wallGenerator(sf::Vector2f, sf::Vector2f);