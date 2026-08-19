#include "wall.h"
#include "constants.h"

Wall::Wall(sf::Vector2f dimensions){

    rec.setSize(dimensions);
    rec.setFillColor(sf::Color::White);
    shape = &rec;
}

Wall::Wall(const Wall& other): Entity(other)
{
    shape = &rec;
}

std::unique_ptr<Entity> Wall::clone() const {
    return std::make_unique<Wall>(*this);
}

void Wall::setDimensions(sf::Vector2f dim){
    rec.setSize(dim);
}

Wall wallGenerator(sf::Vector2f dimensions, sf::Vector2f position){

    Wall wall(dimensions);
    wall.setPosition(position);

    return wall;
}
