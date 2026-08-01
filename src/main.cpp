#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>

int main(){

    std::cout << "Cmake" << std::endl;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML - Physics Engine");
    
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    std::vector <int> temp;


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
        if (ImGui::Button("Click Me!")){
            temp.push_back(1);
        }
        ImGui::End();
        
        for(int i = 0; i < (int)temp.size(); i++){

            std::string str = "##Window" + std::to_string(i);
        
            ImGui::Begin(str.c_str());
            ImGui::Text("Hello Again!");
            ImGui::End();
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

