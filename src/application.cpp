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
    float* m = &mass;
    std::string title = "Input Window";

    float rad;
    
    
    if (selectedBall[0] != -1){

        std::vector <Ball>& arr = findArr(selectedBall[0]);
        
        std::unordered_map <std::string, sf::Vector2f*> pointers = arr[selectedBall[1]].getPointers();
        std::unordered_map <std::string, float*> pointersFloat = arr[selectedBall[1]].getPointersFloat();

        pos = &pointers["position"] -> x;
        vel = &pointers["velocity"] -> x;
        acc = &pointers["acceleration"] -> x;
        m = pointersFloat["mass"];

        rad = arr[selectedBall[1]].getRadius();

        if (selectedBall[0] == 0){
            title = "Ball " + std::to_string(selectedBall[1]) + " (Buffer)";
        }
        else if(selectedBall[0] == 1){
            title = "Ball " + std::to_string(selectedBall[1]) + " (Array)";
        }
    }
    
    ImGui::SFML::Update(window, dt);
    ImGui::Begin(title.c_str());

    if (selectedBall[0] != -1){
        ImGui::InputFloat("Radius", &rad);

        std::vector <Ball>& arr = findArr(selectedBall[0]);
        arr[selectedBall[1]].setRadius(rad);

    }
    else{
        ImGui::InputFloat("Radius", &radius);
    
    }

    ImGui::InputFloat2("Position", pos);         //both store x and y contiguosly so passing the x value will pass both
    ImGui::InputFloat2("Velocity", vel); 
    ImGui::InputFloat2("Acceleration", acc);
    ImGui::InputFloat("Mass", m);
    

    if (selectedBall[0] == -1){

        ImGui::Checkbox("Enable Gravity", &gravityEnabled);
        ImGui::Checkbox("Enable World Borders", &worldBorderEnabled);
        ImGui::Checkbox("Enable Collisions", &collisionEnabled);
    }

    if (worldBorderEnabled && selectedBall[0] == -1){
        ImGui::InputFloat("Restitution (Border)", &resBorder);
    }
    if (collisionEnabled && selectedBall[0] == -1){
        ImGui::InputFloat("Restitution (Ball)", &resBall);
    }


    if (selectedBall[0] == -1 && ImGui::Button("Add")){
        Ball ball = ballGenerator(radius, position, velocity, acceleration, mass);
        ballBuffer.push_back(ball);
    }

    if (selectedBall[0] == -1 && ImGui::Button("Simulate")){

        for(int i = 0; i < (int)ballBuffer.size(); i++){
            ballArr.push_back(ballBuffer[i]);
        }
        ballBuffer.clear();
    }

    ImGui::SameLine();
    if (selectedBall[0] == -1 && ImGui::Button("Clear")){
        ballArr.clear();
        ballBuffer.clear();
    }

    if (selectedBall[0] != -1){
        if (ImGui::Button("Delete")){

            std::vector <Ball>& arr = findArr(selectedBall[0]);
            arr.erase(arr.begin() + selectedBall[1]);

            selectedBall[0] = -1;
            selectedBall[1] = -1;
        }
    }
    if (selectedBall[0] == 0 && ImGui::Button("Simulate")){

        ballArr.push_back(ballBuffer[selectedBall[1]]);
        ballBuffer.erase(ballBuffer.begin() + selectedBall[1]);

        selectedBall[0] = -1;
        selectedBall[1] = -1;
    }

    ImGui::End();
    
}

std::vector<Ball>& Application::findArr(int id){

    if (id == 0){
        return ballBuffer;
    }
    if (id == 1){
        return ballArr;
    }
    throw std::invalid_argument("findArr: Invalid id");
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
            Collision::worldBorder(ballArr[i], resBorder);
        }

        if (collisionEnabled){

            for(int j = i + 1; j < (int)ballArr.size(); j++){
                Collision::ballToBall(ballArr[i], ballArr[j], resBall);
            }
        }
        
        ballArr[i].drawBall(window);
    }

    for(int i = 0; i < (int)ballBuffer.size(); i++){
        ballBuffer[i].setShapePosition();
        ballBuffer[i].drawBall(window);
    }

}

bool Application::checkClick(std::vector <Ball> arr, int id, sf::Vector2f mousePosition){

    for(int i = 0; i < (int)arr.size(); i++){

        sf::Vector2f position = arr[i].getPosition();
        
        sf::Vector2f distanceVector = mousePosition - position;

        float distance = (distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y);

        float radius = arr[i].getRadius();

        if (distance < radius*radius){
            selectedBall[0] = id;
            selectedBall[1] = i;
            return true;
        }

    }

    return false;

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


    if (checkClick(ballBuffer, 0, mousePosition)){
        return;
    }
    
    if (checkClick(ballArr, 1, mousePosition)){
        return;
    }
    
    selectedBall[0] = -1;
    selectedBall[1] = -1;

}

