#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_stdlib.h>
#include "ball.h"
#include <vector>
#include "application.h"

void Application::run(){

    int length = 800;
    int width = 600;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned int> (length), static_cast<unsigned int> (width)}), "SFML - Physics Engine");

    (void)ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    sf::Vector2f position, velocity, acceleration;
    float radius;

    std::vector <Ball> ballArr;

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
            Ball ball = ballGenerator(radius, position, velocity, acceleration);
            ballArr.push_back(ball);
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")){
            ballArr.clear();
        }
        ImGui::End();
        
        window.clear();

        for (int i = 0; i < (int)ballArr.size(); i++){

            ballArr[i].update(dt.asSeconds());
            ballArr[i].drawBall(window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    
}

