#include "entity.h"
#include "constants.h"

Entity::Entity(const Entity& other): position(other.position), shape(other.shape){
    
}

void Entity::setPosition(sf::Vector2f pos){
    position = pos;
}

sf::Vector2f Entity::getPosition(){
    return position;
}

void Entity::drawShape(sf::RenderWindow& window){
    window.draw(*shape);
}

void Entity::setShapePosition(){
    (*shape).setPosition(position * PIXELS_PER_METER);
}