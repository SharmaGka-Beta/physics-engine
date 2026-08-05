#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include "ball.h"
#include <vector>
#include "application.h"
#include "universal.h"
#include "constants.h"
#include "collision.h"

void Application::run(){

    sf::RenderWindow window(sf::VideoMode({WINDOW_LENGTH, WINDOW_WIDTH}), "SFML - Physics Engine");

    (void)ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    // sf::Vector2f position, velocity, acceleration;
    // float radius;

    // std::vector <Ball> ballArr;

    // bool gravityEnabled = false;
    // bool worldBorderEnabled = false;

    while(window.isOpen()){

        runEvents(window);
        sf::Time dt = deltaClock.restart();

        setGui(window, dt);

        updateSimulation(window, dt);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
}

void Application::runEvents(sf::RenderWindow& window){
    
    while(const auto event = window.pollEvent()){

        ImGui::SFML::ProcessEvent(window, *event);
        if (event -> is <sf::Event::Closed>()){
            window.close();
        }
    }
}

void Application::setGui(sf::RenderWindow& window, sf::Time dt){

    ImGui::SFML::Update(window, dt);
    ImGui::Begin("Input Window");

    ImGui::InputFloat("Radius", &radius);
    

    ImGui::InputFloat2("Position", &position.x);         //both store x and y contiguosly so passing the x value will pass both
    ImGui::InputFloat2("Velocity", &velocity.x); 
    ImGui::InputFloat2("Acceleration", &acceleration.x);
    

    ImGui::Checkbox("Enable Gravity", &gravityEnabled);
    ImGui::Checkbox("Enable World Borders", &worldBorderEnabled);

    if (gravityEnabled){
        Universal :: setAccelerationUniversal({0.f, static_cast <float> (9.8 * PIXELS_PER_METER)});
    }
    else{
        Universal :: setAccelerationUniversal({0.f, 0.f});
    }

    if (ImGui::Button("Simulate")){
        Ball ball = ballGenerator(radius, position, velocity, acceleration);
        ballArr.push_back(ball);
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")){
        ballArr.clear();
    }
    ImGui::End();
    
    window.clear();
}

void Application::updateSimulation(sf::RenderWindow& window, sf::Time dt){

    for (int i = 0; i < (int)ballArr.size(); i++){

        ballArr[i].update(dt.asSeconds());

        if (worldBorderEnabled){
            Collision::worldBorder(ballArr[i]);
        }
        
        ballArr[i].drawBall(window);
    }

}

