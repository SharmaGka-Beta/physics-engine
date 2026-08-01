#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>
#include <imgui_stdlib.h>
#include <optional>
#include "ball.h"

int main(){

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML - Physics Engine");
    
    (void)ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    sf::Vector2f position, velocity, acceleration;

    float radius;

    std::optional <Ball> ball;

    while(window.isOpen()){
        while(const auto event = window.pollEvent()){

            ImGui::SFML::ProcessEvent(window, *event);
            if (event -> is <sf::Event::Closed>()){
                window.close();
            }
        }

        sf::Time dt = deltaClock.restart();
        ImGui::SFML::Update(window, dt);
        ImGui::Begin("Input Window");

        ImGui::InputFloat("Radius", &radius);

        ImGui::InputFloat2("Position", &position.x);         //both store x and y contiguosly so passing the x value will pass both
        ImGui::InputFloat2("Velocity", &velocity.x); 
        ImGui::InputFloat2("Acceleration", &acceleration.x); 

        if (ImGui::Button("Simulate")){
            ball = ballGenerator(radius, position, velocity, acceleration);
        }
        ImGui::End();
        

        window.clear();

        if (ball){

            ball -> update(dt.asSeconds());
            ball -> drawBall(window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

