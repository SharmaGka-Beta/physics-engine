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
        ImGui::End();
        
        window.clear();

        // for(int i = 0; i < (int)ballArr.size();){
        //     if (ballArr[i].getPosition().x < -ballArr[i].getRadius() || ballArr[i].getPosition().x > length + ballArr[i].getRadius()){
        //         std::swap(ballArr[i], ballArr.back());
        //         ballArr.pop_back();
        //         continue;
        //     }
        //     if (ballArr[i].getPosition().y < -ballArr[i].getRadius() || ballArr[i].getPosition().y > width + ballArr[i].getRadius()){
        //         std::swap(ballArr[i], ballArr.back());
        //         ballArr.pop_back();
        //         continue;
        //     }
        //     i++;
        // }

        for (int i = 0; i < (int)ballArr.size(); i++){

            ballArr[i].update(dt.asSeconds());
            ballArr[i].drawBall(window);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

