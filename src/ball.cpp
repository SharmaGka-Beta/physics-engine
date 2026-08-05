#include <ball.h>
#include "constants.h"
#include <string>


Ball::Ball(float radius){
    obj.setRadius(radius);
    obj.setFillColor(sf::Color::White);
    obj.setOrigin({radius, radius});
}

void Ball::drawBall(sf::RenderWindow& window){        
    window.draw(obj);
}                                                  //Top functions control the gui and observable ball. Bottom functions control the stored values.
void Ball::setShapePosition(){
    obj.setPosition(position);
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
void Ball::update(float dt){
    
    
    velocity = velocity + (acceleration + getAccelerationUniversal())*dt;
    position = position + (velocity + getVelocityUniversal())*dt;
    setShapePosition();
}

sf::Vector2f Ball::getPosition(){
    return position;
}

sf::Vector2f Ball::getVelocity(){
    return velocity;
}

float Ball::getRadius(){
    return obj.getRadius();
}
std::unordered_map <std::string, sf::Vector2f*> Ball::getPointers(){
    return {{"position", &position},
            {"velocity", &velocity},
            {"acceleration", &acceleration}};
}


Ball ballGenerator(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration){

    radius = radius * PIXELS_PER_METER;
    position = {position.x * PIXELS_PER_METER, position.y * PIXELS_PER_METER};
    velocity = {velocity.x * PIXELS_PER_METER, velocity.y * PIXELS_PER_METER};
    acceleration = {acceleration.x * PIXELS_PER_METER, acceleration.y * PIXELS_PER_METER};

    Ball ball(radius);
    ball.setPosition(position);
    
    ball.setVelocity(velocity);
    ball.setAcceleration(acceleration);

    return ball ;

}