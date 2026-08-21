#include <SFML/Graphics.hpp>

#include "wall.h"
#include "constants.h"

Wall::Wall(sf::Vector2f dimensions, sf::Angle degree){

    rec.setSize(dimensions * PIXELS_PER_METER);
    rec.setFillColor(sf::Color::White);
    rec.setOrigin({dimensions.x * PIXELS_PER_METER / 2.f, dimensions.y * PIXELS_PER_METER / 2.f});
    rec.setRotation(degree);
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
    rec.setSize(dim * PIXELS_PER_METER);
    rec.setOrigin({dim.x * PIXELS_PER_METER / 2.f, dim.y * PIXELS_PER_METER / 2.f});
}

sf::Vector2f Wall::getDimensions(){
    return rec.getSize()/PIXELS_PER_METER;
}

float Wall::getAngle(){
    return rec.getRotation().asRadians();
}

void Wall::setAngle(sf::Angle deg){
    rec.setRotation(deg);
}

std::unique_ptr<Wall> wallGenerator(sf::Vector2f dimensions, sf::Vector2f position, sf::Angle degree){

    auto wall = std::make_unique<Wall>(dimensions, degree);

    wall -> setPosition(position);

    return wall;
}
