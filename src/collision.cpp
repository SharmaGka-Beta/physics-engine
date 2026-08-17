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
        // position.x = radius;
        velocity.x = velocity.x * (-1.f) * coeffRestitution;
    }
    else if(position.x >= WINDOW_LENGTH - radius){
        // position.x = WINDOW_LENGTH - radius;
        velocity.x = velocity.x * (-1.f) * coeffRestitution; 

    }
    if (position.y <= radius){
        // position.y = radius;
        velocity.y = velocity.y * (-1.f) * coeffRestitution;

    }
    else if(position.y >= WINDOW_WIDTH - radius){
        // position.y = WINDOW_WIDTH - radius;
        velocity.y = velocity.y * (-1.f) * coeffRestitution;

    }

    ball.setPosition(position);
    ball.setVelocity(velocity);
}

void Collision::ballToBall(Ball& ball1, Ball& ball2, float e){

    sf::Vector2f pos1 = ball1.getPosition();
    sf::Vector2f pos2 = ball2.getPosition();
    sf::Vector2f delta = pos2 - pos1;

    float rad1 = ball1.getRadius();
    float rad2 = ball2.getRadius();
    float maxDist = rad1 + rad2;

    float distSq = delta.x*delta.x + delta.y*delta.y;
    if (distSq > maxDist*maxDist){
        return;
    }

    float dist = std::sqrt(distSq);

    sf::Vector2f n = delta / dist; 

    float m1 = ball1.getMass();
    float m2 = ball2.getMass();

    sf::Vector2f u1 = ball1.getVelocity();
    sf::Vector2f u2 = ball2.getVelocity();

    sf::Vector2f relVel = u2 - u1;
    float vn = relVel.x*n.x + relVel.y*n.y;

    if (vn > 0.f){
        return;   
    }

    float j = -(1.f + e) * vn / (1.f/m1 + 1.f/m2);

    sf::Vector2f impulse = j * n;

    sf::Vector2f v1 = u1 - impulse/m1;
    sf::Vector2f v2 = u2 + impulse/m2;

    ball1.setVelocity(v1);
    ball2.setVelocity(v2);
    
}


