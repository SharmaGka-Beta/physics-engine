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
        sf::Vector2f dimensions = {};

        float resBorder = 1;
        float resBall = 1;

        std::vector <std::unique_ptr <Entity>> entityArr;         // termed as 1 for selectedBall
        std::vector <std::unique_ptr <Entity>> entityBuffer;      // termed as 0 for selectedBall
        std::vector <std::unique_ptr <Entity>> saveArr;
        std::vector <std::unique_ptr <Entity>> saveBuffer;

        bool gravityEnabled = false;
        bool worldBorderEnabled = false;
        bool collisionEnabled = false;
        bool displayAddGui = false;

        void runEvents(sf::RenderWindow&);
        void setGui(sf::RenderWindow&, sf::Time);
        void updateSimulation(sf::RenderWindow&, sf::Time);

        void ballEditGui();
        void ballAddGui();
        void wallAddGui();

        void mainGui();
        void moveWithKeys();
        
        void save();
        void loadSave();

        void checkSelectedBall(sf::RenderWindow&);
        bool checkClick(std::vector <std::unique_ptr <Entity>>&, int, sf::Vector2f);
        std::vector <std::unique_ptr <Entity>>& findArr(int);

        

    public:
        void run();
};