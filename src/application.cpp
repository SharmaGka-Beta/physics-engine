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
#include "entity.h"
#include "wall.h"

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

    ImGui::SFML::Update(window, dt);

    
    if (selectedBall[0] != -1 && dynamic_cast<Ball*>(findArr(selectedBall[0])[selectedBall[1]].get())){         //check to see if object is ball/wall
        ballEditGui();
    }
    else if(selectedBall[0] != -1 && dynamic_cast<Wall*>(findArr(selectedBall[0])[selectedBall[1]].get())){
        wallEditGui();
    }
    else if(displayAddGui == 0){
        ballAddGui();
    }
    else if(displayAddGui == 1){
        wallAddGui();
    }
    else{
        mainGui();
    }

    
}

void Application::mainGui(){

    std::string title = "Input Window";

    ImGui::Begin(title.c_str());

    if (ImGui::Button("Add Ball")){
        displayAddGui = 0;
    }

    ImGui::SameLine();

    if (ImGui::Button("Add Wall")){
        displayAddGui = 1;
    }

    ImGui::Checkbox("Enable Gravity", &gravityEnabled);
    ImGui::Checkbox("Enable World Borders", &worldBorderEnabled);
    ImGui::Checkbox("Enable Collisions", &collisionEnabled);

    if (worldBorderEnabled){
        ImGui::InputFloat("Restitution (Border)", &resBorder);
    }
    if (collisionEnabled){
        ImGui::InputFloat("Restitution (Ball)", &resBall);
    }

    if (ImGui::Button("Simulate")){

        for(int i = 0; i < (int)entityBuffer.size(); i++){
            entityArr.push_back(std::move(entityBuffer[i]));
        }
        entityBuffer.clear();
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")){
        for(int i = 0; i < (int)entityArr.size(); i++){
            entityBuffer.push_back(std::move(entityArr[i]));
        }
        entityArr.clear();
    }
    ImGui::SameLine();

    if (ImGui::Button("Clear")){
        entityArr.clear();
        entityBuffer.clear();
    }

    if (ImGui::Button("Save")){
        save();
    }
    ImGui::SameLine();

    if (!(saveArr.empty() && saveBuffer.empty())){
        if (ImGui::Button("Load")){
            loadSave();
        }
    }

    ImGui::End();
}

void Application::ballAddGui(){

    float* pos = &position.x;
    float* vel = &velocity.x;
    float* acc = &acceleration.x;
    float* m = &mass;

    std::string title = "Add Ball";

    ImGui::Begin(title.c_str());

    ImGui::InputFloat("Radius", &radius);

    ImGui::InputFloat2("Position", pos);         //both store x and y contiguosly so passing the x value will pass both
    ImGui::InputFloat2("Velocity", vel); 
    ImGui::InputFloat2("Acceleration", acc);
    ImGui::InputFloat("Mass", m);

    if (ImGui::Button("Add")){
        auto ball = ballGenerator(radius, position, velocity, acceleration, mass);
        entityBuffer.push_back(std::move(ball));
    }
    ImGui::SameLine();
    if (ImGui::Button("Simulate")){
        auto ball = ballGenerator(radius, position, velocity, acceleration, mass);
        entityArr.push_back(std::move(ball));
    }

    if (ImGui::Button("Back")){
        displayAddGui = -1;
    }

    ImGui::End();

}

void Application::wallAddGui(){

    float* pos = &position.x;
    float* dim = &dimensions.x;

    std::string title = "Add Wall";

    ImGui::Begin(title.c_str());

    ImGui::InputFloat2("Dimensions", dim);
    ImGui::InputFloat2("Position", pos);

    if (ImGui::Button("Add")){
        auto wall = wallGenerator(dimensions, position);
        entityArr.push_back(std::move(wall));
    }

    if (ImGui::Button("Back")){
        displayAddGui = -1;
    }


    ImGui::End();
}

void Application::ballEditGui(){

    std::vector <std::unique_ptr <Entity>>& arr = findArr(selectedBall[0]);

    Ball* ball = dynamic_cast<Ball*>(arr[selectedBall[1]].get());

    if (!ball){
        return;
    }
        
    std::unordered_map <std::string, sf::Vector2f*> pointers = ball -> getPointersVectors();
    std::unordered_map <std::string, float*> pointersFloat = ball -> getPointersFloat();
    
    float* pos = &pointers["position"] -> x;
    float* vel = &pointers["velocity"] -> x;
    float* acc = &pointers["acceleration"] -> x;
    float* m = pointersFloat["mass"];
    std::string title;

    float rad = ball -> getRadius();

    if (selectedBall[0] == 0){
        title = "Ball " + std::to_string(selectedBall[1]) + " (Buffer)";
    }
    else if(selectedBall[0] == 1){
        title = "Ball " + std::to_string(selectedBall[1]) + " (Array)";
    }

    ImGui::Begin(title.c_str());

    ImGui::InputFloat("Radius", &rad);
    ImGui::InputFloat2("Position", pos);       
    ImGui::InputFloat2("Velocity", vel); 
    ImGui::InputFloat2("Acceleration", acc);
    ImGui::InputFloat("Mass", m);

    ball -> setRadius(rad);

    if (selectedBall[0] == 0){

        if (ImGui::Button("Simulate")){
            
            entityArr.push_back(std::move(entityBuffer[selectedBall[1]]));
            entityBuffer.erase(entityBuffer.begin() + selectedBall[1]);
            
            selectedBall[0] = -1;
            selectedBall[1] = -1;
        }
        ImGui::SameLine();
    }

    if (ImGui::Button("Delete")){
        std::vector <std::unique_ptr <Entity>>& arr = findArr(selectedBall[0]);
        arr.erase(arr.begin() + selectedBall[1]);

        selectedBall[0] = -1;
        selectedBall[1] = -1;
    }
    if (selectedBall[0] != -1){
        moveWithKeys();
    }

    ImGui::End();

}

void Application::wallEditGui(){

    std::vector <std::unique_ptr <Entity>>& arr = findArr(selectedBall[0]);

    Wall* wall = dynamic_cast<Wall*>(arr[selectedBall[1]].get());

    if (!wall){
        return;
    }

    std::unordered_map <std::string, sf::Vector2f*> pointers = wall -> getPointersVectors();

    float* pos = &pointers["position"] -> x;
    sf::Vector2f dim = wall->getDimensions();

    std::string title;

    if (selectedBall[0] == 0){
        title = "Wall " + std::to_string(selectedBall[1]) + " (Buffer)";
    }
    else if(selectedBall[0] == 1){
        title = "Wall " + std::to_string(selectedBall[1]) + " (Array)";
    }

    ImGui::Begin(title.c_str());

    ImGui::InputFloat2("Dimensions", &dim.x);       
    ImGui::InputFloat2("Position", pos);
    
    wall -> setDimensions(dim);

    if (ImGui::Button("Delete")){
        arr.erase(arr.begin() + selectedBall[1]);

        selectedBall[0] = -1;
        selectedBall[1] = -1;
    }

    if (selectedBall[0] != -1){
        moveWithKeys();
    }

    ImGui::End();


}

void Application::save(){

    saveArr.clear();
    for (auto& e : entityArr){
        saveArr.push_back(e->clone());
    }

    saveBuffer.clear();
    for (auto& e : entityBuffer){
        saveBuffer.push_back(e->clone());
    }
}

void Application::loadSave(){
    entityArr.clear();
    for (auto& e : saveArr){
        entityArr.push_back(e->clone());
    }

    entityBuffer.clear();
    for (auto& e : saveBuffer){
        entityBuffer.push_back(e->clone());
    }

}


std::vector <std::unique_ptr <Entity>>& Application::findArr(int id){

    if (id == 0){
        return entityBuffer;
    }
    if (id == 1){
        return entityArr;
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

    for (int i = 0; i < (int)entityArr.size(); i++){

        Ball* ball = dynamic_cast<Ball*>(entityArr[i].get());
        Wall* wall = nullptr;

        if (!ball){
            
            wall = dynamic_cast<Wall*>(entityArr[i].get());
            if (!wall){
                continue;
            }
        }

        if (ball){

            ball -> update(dt.asSeconds()); //
            
            if (worldBorderEnabled){ //
                Collision::worldBorder(*ball, resBorder);
            }
            
            if (collisionEnabled){ //
                
                for(int j = i + 1; j < (int)entityArr.size(); j++){
                    
                    Ball* ballNew = dynamic_cast<Ball*>(entityArr[j].get());
                    
                    if (!ballNew){
                        continue;
                    }
                    Collision::ballToBall(*ball, *ballNew, resBall);
                }
            }
        }
        else if(wall){
            wall->setShapePosition();
        }
        
        entityArr[i] -> drawShape(window);
    }

    for(int i = 0; i < (int)entityBuffer.size(); i++){
        entityBuffer[i] -> setShapePosition();
        entityBuffer[i] -> drawShape(window);
    }

}

bool Application::checkClick(std::vector <std::unique_ptr <Entity>>& arr, int id, sf::Vector2f mousePosition){

    for(int i = 0; i < (int)arr.size(); i++){

        Ball* ball = dynamic_cast<Ball*>(arr[i].get());
        Wall* wall;
        

        if (!ball){
            wall = dynamic_cast<Wall*>(arr[i].get());
            if (!wall){
                continue;
            }
        }
        if (ball){

            sf::Vector2f position = ball -> getPosition();
            
            sf::Vector2f distanceVector = mousePosition - position;
            
            float distance = (distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y);
            
            float radius = ball -> getRadius();
            
            if (distance < radius*radius){
                selectedBall[0] = id;
                selectedBall[1] = i;
                return true;
            }
        }
        else if(wall){

            sf::Vector2f position = wall -> getPosition();
            sf::Vector2f dimensions = wall->getDimensions();

            if (mousePosition.x < position.x - dimensions.x/2.f || mousePosition.x > position.x + dimensions.x/2.f || mousePosition.y < position.y - dimensions.y/2.f || mousePosition.y > position.y + dimensions.y/2.f){

                continue;
            }

            selectedBall[0] = id;
            selectedBall[1] = i;
            return true;
        }

    }

    return false;

}

void Application::moveWithKeys(){

    std::vector <std::unique_ptr <Entity>>& arr = findArr(selectedBall[0]);
    sf::Vector2f pos = arr[selectedBall[1]] -> getPosition();


    float delx = 0;
    float dely = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){

        delx += 0.001f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){

        delx -= 0.001f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){

        dely -= 0.001f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){

        dely += 0.001f;
    }
    arr[selectedBall[1]] -> setPosition({pos.x + delx, pos.y + dely});
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


    if (checkClick(entityBuffer, 0, mousePosition)){
        return;
    }
    
    if (checkClick(entityArr, 1, mousePosition)){
        return;
    }
    
    selectedBall[0] = -1;
    selectedBall[1] = -1;

}

