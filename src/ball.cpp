#include "ball.h"
#include "constants.h"
#include <string>


Ball::Ball(float radius){
    obj.setRadius(radius * PIXELS_PER_METER);
    obj.setFillColor(sf::Color::White);
    obj.setOrigin({radius * PIXELS_PER_METER, radius * PIXELS_PER_METER});
    shape = &obj;
}

Ball::Ball(const Ball& other)
    : Universal(other), Entity(other),
      velocity(other.velocity), acceleration(other.acceleration),
      obj(other.obj), mass(other.mass)
{
    shape = &obj;
}

std::unique_ptr<Entity> Ball::clone() const {
    return std::make_unique<Ball>(*this);
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

void Ball::setMass(float m){
    mass = m;
}


sf::Vector2f Ball::getVelocity(){
    return velocity;
}

float Ball::getRadius(){
    return obj.getRadius() / PIXELS_PER_METER;
}

float Ball::getMass(){
    return mass;
}

std::unordered_map <std::string, sf::Vector2f*> Ball::getPointersVectors(){
    return {{"position", &position},
            {"velocity", &velocity},
            {"acceleration", &acceleration},
            };
}

std::unordered_map <std::string, float*> Ball::getPointersFloat(){
    return {{"mass", &mass}};
}


std::unique_ptr<Ball> ballGenerator(float radius, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, float mass){

    auto ball = std::make_unique<Ball>(radius);

    ball -> setPosition(position);
    
    ball -> setVelocity(velocity);
    ball -> setAcceleration(acceleration);

    ball -> setMass(mass);

    return ball ;

}