#include <SFML/Graphics.hpp>
#include <iostream>

#include "ball.h"
#include "collision.h"
#include "constants.h"

void Collision :: worldBorder(Ball& ball, float e){

    sf::Vector2f velocity = ball.getVelocity();
    sf::Vector2f position = ball.getPosition();
    float radius = ball.getRadius();


    if (position.x <= radius && position.x > -radius){
        position.x = radius;
        velocity.x = velocity.x * (-1.f) * e;
    }
    else if(position.x >= WINDOW_LENGTH - radius && position.x < WINDOW_LENGTH + radius){
        position.x = WINDOW_LENGTH - radius;
        velocity.x = velocity.x * (-1.f) * e; 

    }
    if (position.y <= radius && position.y > -radius){
        position.y = radius;
        velocity.y = velocity.y * (-1.f) * e;

    }
    else if(position.y >= WINDOW_WIDTH - radius && position.y < WINDOW_WIDTH + radius){
        position.y = WINDOW_WIDTH - radius;
        velocity.y = velocity.y * (-1.f) * e;

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

void Collision::ballToWall(Ball& ball, Wall& wall, float e){

    sf::Vector2f ballPos = ball.getPosition();
    sf::Vector2f velocity = ball.getVelocity();
    float radius = ball.getRadius();


    sf::Vector2f wallPos = wall.getPosition();
    sf::Vector2f wallDim = wall.getDimensions();
    sf::Angle wallAngle = sf::radians(wall.getAngle());

    float c = std::cos(wallAngle.asRadians());
    float s = std::sin(wallAngle.asRadians());

    sf::Vector2f xAxis = {c, s};
    sf::Vector2f yAxis = {-s, c};

    sf::Vector2f rel = ballPos - wallPos;

    float localX = rel.x * xAxis.x + rel.y * xAxis.y;
    float localY = rel.x * yAxis.x + rel.y * yAxis.y; 

    float halfW = wallDim.x / 2.f;
    float halfH = wallDim.y / 2.f;

    float clampedX = std::clamp(localX, -halfW, halfW);
    float clampedY = std::clamp(localY, -halfH, halfH);

    float deltaX = localX - clampedX;
    float deltaY = localY - clampedY;
    float distSq = deltaX * deltaX + deltaY * deltaY;

    if (distSq >= radius * radius){
        return;
    }

    float dist = std::sqrt(distSq);

    sf::Vector2f worldNormal;

    if (dist > 0.0001f){
        float invDist = 1.f / dist;
        worldNormal = xAxis * (deltaX * invDist) + yAxis * (deltaY * invDist);
    } 
    else{
        worldNormal = yAxis;
    }


    float penetration = radius - dist;
    ballPos += worldNormal * penetration;

    float vDotN = velocity.x * worldNormal.x + velocity.y * worldNormal.y;
    if (vDotN < 0.f){
        velocity = velocity - worldNormal * (1.f + e) * vDotN;
    }
    
    ball.setPosition(ballPos);
    ball.setVelocity(velocity);


}


