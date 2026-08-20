#pragma once

#include <SFML/Graphics.hpp>

class Entity{

    private:
        

    public:

        virtual std::unordered_map <std::string, sf::Vector2f*> getPointersVectors();
        virtual std::unordered_map <std::string, float*> getPointersFloat();

        virtual std::unique_ptr<Entity> clone() const = 0;
        
        Entity() = default;
        Entity(const Entity& other);
        virtual ~Entity() = default;

        void setPosition(sf::Vector2f);
        sf::Vector2f getPosition();

        void drawShape(sf::RenderWindow& window);
        void setShapePosition();

    protected:
        sf::Vector2f position{};
        sf::Shape* shape = nullptr;


};