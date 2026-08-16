#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.h"

class Application{

    private:

        sf::Vector2f position{};
        sf::Vector2f velocity{};
        sf::Vector2f acceleration{};
        int mass = 1;
        int selectedBall = -1;

        float radius = 0.f;

        float coeffRestitution = 1;

        std::vector <Ball> ballArr;

        bool gravityEnabled = false;
        bool worldBorderEnabled = false;

        void runEvents(sf::RenderWindow&);
        void setGui(sf::RenderWindow&, sf::Time);
        void updateSimulation(sf::RenderWindow&, sf::Time);

        void checkSelectedBall(sf::RenderWindow&);

        

    public:
        void run();
};