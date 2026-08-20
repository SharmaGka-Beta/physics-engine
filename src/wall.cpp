#include "wall.h"
#include "constants.h"

Wall::Wall(sf::Vector2f dimensions){

    rec.setSize(dimensions);
    rec.setFillColor(sf::Color::White);
    rec.setOrigin({dimensions.x * PIXELS_PER_METER, dimensions.y * PIXELS_PER_METER});
    shape = &rec;
}

Wall::Wall(const Wall& other): Entity(other), rec(other.rec)
{
    shape = &rec;
}

std::unique_ptr<Entity> Wall::clone() const {
    return std::make_unique<Wall>(*this);
}

void Wall::setDimensions(sf::Vector2f dim){
    rec.setSize(dim);
}

std::unique_ptr<Wall> wallGenerator(sf::Vector2f dimensions, sf::Vector2f position){

    auto wall = std::make_unique<Wall>(dimensions);

    wall -> setPosition(position);

    return wall;
}
