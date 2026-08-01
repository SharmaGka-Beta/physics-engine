#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

int main(){

    std::cout << "Cmake" << std::endl;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML - Physics Engine");
    
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

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
        if(ImGui::Button("Click me")){
            std::cout << "Clicked\n";
        }

        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

