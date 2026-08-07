#include "collision.h"
#include "ball.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Collision :: worldBorder(Ball& ball, float coeffRestitution){

    sf::Vector2f velocity = ball.getVelocity();
    sf::Vector2f position = ball.getPosition();
    float radius = ball.getRadius();


    if (position.x <= radius){
        position.x = radius;
        velocity.x = velocity.x * (-1.f) * coeffRestitution;
    }
    else if(position.x >= WINDOW_LENGTH - radius){
        position.x = WINDOW_LENGTH - radius;
        velocity.x = velocity.x * (-1.f) * coeffRestitution; 

    }
    if (position.y <= radius){
        position.y = radius;
        velocity.y = velocity.y * (-1.f) * coeffRestitution;

    }
    else if(position.y >= WINDOW_WIDTH - radius){
        position.y = WINDOW_WIDTH - radius;
        velocity.y = velocity.y * (-1.f) * coeffRestitution;

    }

    ball.setPosition(position);
    ball.setVelocity(velocity);
}


