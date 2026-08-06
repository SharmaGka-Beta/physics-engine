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
#include <iostream>
#include <string>

void Application::run(){

    sf::RenderWindow window(sf::VideoMode({static_cast <unsigned int> (WINDOW_LENGTH* PIXELS_PER_METER), 
                                            static_cast <unsigned int> (WINDOW_WIDTH * PIXELS_PER_METER)}), 
                                            "SFML - Physics Engine");

    (void)ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while(window.isOpen()){

        runEvents(window);
        sf::Time dt = deltaClock.restart();

        checkSelectedBall(window);

        setGui(window, dt);

        window.clear();

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

    float* pos = &position.x;
    float* vel = &velocity.x;
    float* acc = &acceleration.x;
    std::string title = "Input Window";

    float rad;
    
    if (selectedBall != -1){
        std::unordered_map <std::string, sf::Vector2f*> pointers = ballArr[selectedBall].getPointers();
        pos = &pointers["position"] -> x;
        vel = &pointers["velocity"] -> x;
        acc = &pointers["acceleration"] -> x;
        rad = ballArr[selectedBall].getRadius();
        title = "Ball " + std::to_string(selectedBall);
    }

    ImGui::SFML::Update(window, dt);
    ImGui::Begin(title.c_str());

    if (selectedBall != -1){
        ImGui::InputFloat("Radius", &rad);
        ballArr[selectedBall].setRadius(radius);
    }
    else{
        ImGui::InputFloat("Radius", &radius);
    
    }

    ImGui::InputFloat2("Position", pos);         //both store x and y contiguosly so passing the x value will pass both
    ImGui::InputFloat2("Velocity", vel); 
    ImGui::InputFloat2("Acceleration", acc);
    

    ImGui::Checkbox("Enable Gravity", &gravityEnabled);
    ImGui::Checkbox("Enable World Borders", &worldBorderEnabled);


    if (ImGui::Button("Simulate")){
        Ball ball = ballGenerator(radius, position, velocity, acceleration);
        ballArr.push_back(ball);
    }
    ImGui::SameLine();
    if (ImGui::Button("Clear")){
        selectedBall = -1;
        ballArr.clear();
    }
    ImGui::End();
    
}

void Application::updateSimulation(sf::RenderWindow& window, sf::Time dt){

    if (gravityEnabled){
        Universal :: setAccelerationUniversal({0.f, static_cast <float> (9.8)});
    }
    else{
        Universal :: setAccelerationUniversal({0.f, 0.f});
    }

    for (int i = 0; i < (int)ballArr.size(); i++){

        ballArr[i].update(dt.asSeconds());

        if (worldBorderEnabled){
            Collision::worldBorder(ballArr[i]);
        }
        
        ballArr[i].drawBall(window);
    }

}

void Application::checkSelectedBall(sf::RenderWindow& window){

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        return;
    }

    if (ImGui::GetIO().WantCaptureMouse){
        return;
    }

    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);

    if (mousePixel.x < 0 || mousePixel.x >= static_cast<int>(WINDOW_LENGTH * PIXELS_PER_METER) || 
        mousePixel.y < 0 || mousePixel.y >= static_cast<int>(WINDOW_WIDTH * PIXELS_PER_METER)){
        return;
    }
    
    sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixel) / PIXELS_PER_METER;

    for(int i = 0; i < (int)ballArr.size(); i++){

        sf::Vector2f position = ballArr[i].getPosition();

        sf::Vector2f distanceVector = mousePosition - position;

        float distance = (distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y);

        float radius = ballArr[i].getRadius();

        if (distance < radius * radius){
            selectedBall = i;
            return;
        }
    }
    selectedBall = -1;

}

