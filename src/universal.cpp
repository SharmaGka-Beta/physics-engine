#include "universal.h"
#include <SFML/Graphics.hpp>

sf::Vector2f Universal :: velocityUniversal = {0.f, 0.f};
sf::Vector2f Universal :: accelerationUniversal = {0.f, 0.f};


void Universal :: setVelocityUniversal(sf::Vector2f vel){
    velocityUniversal = vel;
}

void Universal :: setAccelerationUniversal(sf::Vector2f acc){
    accelerationUniversal = acc;
}

sf::Vector2f Universal :: getVelocityUniversal(){
    return velocityUniversal;
}

sf::Vector2f Universal :: getAccelerationUniversal(){
    return accelerationUniversal;
}