#include "wall.h"
#include "constants.h"

Wall::Wall(sf::Vector2f dimensions){

    rec.setSize(dimensions);
    rec.setFillColor(sf::Color::White);
}

void Wall::drawWall(sf::RenderWindow& window){
    window.draw(rec);
}

void Wall::setShapePosition(){
    rec.setPosition(position * PIXELS_PER_METER);
}

void Wall::setPosition(sf::Vector2f pos){
    position = pos;
}

void Wall::setDimensions(sf::Vector2f dim){
    rec.setSize(dim);
}

Wall wallGenerator(sf::Vector2f dimensions, sf::Vector2f position){

    Wall wall(dimensions);
    wall.setPosition(position);

    return wall;
}
