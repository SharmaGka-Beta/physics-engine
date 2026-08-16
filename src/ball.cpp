#include <ball.h>
#include "constants.h"
#include <string>


Ball::Ball(float radius){
    obj.setRadius(radius * PIXELS_PER_METER);
    obj.setFillColor(sf::Color::White);
    obj.setOrigin({radius * PIXELS_PER_METER, radius * PIXELS_PER_METER});
}

void Ball::drawBall(sf::RenderWindow& window){        
    window.draw(obj);
}                                                  //Top functions control the gui and observable ball. Bottom functions control the stored values.
void Ball::setShapePosition(){
    obj.setPosition(position * PIXELS_PER_METER);
}

void Ball::setPosition(sf::Vector2f pos){
    position = pos;
}

void Ball::setVelocity(sf::Vector2f vel){
    velocity = vel;
}

void Ball::setAcceleration(sf::Vector2f acc){
    acceleration = acc;
}

void Ball::setRadius(float radius){
    obj.setRadius(radius * PIXELS_PER_METER);
    obj.setOrigin({radius * PIXELS_PER_METER, radius * PIXELS_PER_METER});
}

void Ball::update(float dt){
    
    velocity = velocity + (acceleration + getAccelerationUniversal())*dt;
    position = position + (velocity + getVelocityUniversal())*dt;
    setShapePosition();
}

void Ball::setMass(int m){
    mass = m;
}

sf::Vector2f Ball::getPosition(){
    return position;
}

sf::Vector2f Ball::getVelocity(){
    return velocity;
}

float Ball::getRadius(){
    return obj.getRadius() / PIXELS_PER_METER;
}
std::unordered_map <std::string, sf::Vector2f*> Ball::getPointers(){
    return {{"position", &position},
            {"velocity", &velocity},
            {"acceleration", &acceleration},
            };
}

std::unordered_map <std::string, int*> Ball::getPointersInt(){
    return {{"mass", &mass}};
}


Ball ballGenerator(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, int mass){

    radius = radius;
    position = {position.x, position.y};
    velocity = {velocity.x, velocity.y};
    acceleration = {acceleration.x, acceleration.y};

    Ball ball(radius);
    ball.setPosition(position);
    
    ball.setVelocity(velocity);
    ball.setAcceleration(acceleration);

    ball.setMass(mass);

    return ball ;

}