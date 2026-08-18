#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.h"
#include "entity.h"

class Application{

    private:

        sf::Vector2f position{};
        sf::Vector2f velocity{};
        sf::Vector2f acceleration{};
        float mass = 1.f;
        std::vector <int> selectedBall = {-1, -1};

        float radius = 0.f;

        float resBorder = 1;
        float resBall = 1;

        std::vector <Ball> ballArr;         // termed as 1 for selectedBall
        std::vector <Ball> ballBuffer;      // termed as 0 for selectedBall
        std::vector <Ball> saveArr;
        std::vector <Ball> saveBuffer;

        bool gravityEnabled = false;
        bool worldBorderEnabled = false;
        bool collisionEnabled = false;
        bool displayAddGui = false;

        void runEvents(sf::RenderWindow&);
        void setGui(sf::RenderWindow&, sf::Time);
        void updateSimulation(sf::RenderWindow&, sf::Time);
        void ballEditGui();
        void ballAddGui();
        void mainGui();
        void moveWithKeys();
        
        void save();
        void loadSave();

        void checkSelectedBall(sf::RenderWindow&);
        bool checkClick(std::vector <Ball>, int, sf::Vector2f);
        std::vector <Ball>& findArr(int);

        

    public:
        void run();
};