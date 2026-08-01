#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>
#include <imgui_stdlib.h>

int main(){

    std::cout << "Cmake" << std::endl;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML - Physics Engine");
    
    (void)ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    std::string temp;

    while(window.isOpen()){
        while(const auto event = window.pollEvent()){

            ImGui::SFML::ProcessEvent(window, *event);
            if (event -> is <sf::Event::Closed>()){
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Test Window");
        ImGui::Text("Hello ImGui!");
        ImGui::InputText("##Inp", &temp);
        if (ImGui::Button("Click Me!")){
            std::cout << temp << std::endl;
        }
        ImGui::End();
        

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

