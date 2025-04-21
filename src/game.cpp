#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "game.h"
#include "entity.h"
#include "player.h"
#include "terrainElement.h"
#include "include/box2d/box2d.h"

using namespace std;

Game::Game(sf::RenderWindow *window, int width, int height, int zeroX, int zeroY) {

    //set display stuff
    this->window = window;
    (*window).clear(sf::Color::Blue);
    windowWidth = width;
    windowHeight = height;
    this->zeroX = zeroX;
    this->zeroY = zeroY;

    //initialize physics
    worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0, gravity};
    worldId = b2CreateWorld(&worldDef);
    b2World_Step(worldId, timeStep, subStepCount);

    //set time
    initialTime = chrono::high_resolution_clock::now();
    time = initialTime;
    deltaTime = chrono::duration<float>(0);
    accumulator = getDeltaTime();

    //create main player
    Player* player = new Player(this, 0.0f, 2.0f);
    TerrainElement* terrainElement0 = new TerrainElement(this, 0.0f, -2.0f, 5.0f, 1.0f);
    TerrainElement* terrainElement1 = new TerrainElement(this, 7.0f, 0.0f, 5.0f, 1.0f);
    TerrainElement* terrainElement2 = new TerrainElement(this, -8.0f, -3.0f, 3.0f, 1.0f);

    cout << "# of entities: " << entities.size() << "\n";

}

Game::Game() {

}

void Game::update() {
    //cout << "running update!\n";

    (*window).clear(sf::Color::Blue);
    
    //update time
    lastTime = time;
    time = chrono::high_resolution_clock::now();
    deltaTime = chrono::duration_cast<chrono::duration<float>>(time - lastTime);

    //update physics
    //cout << "updating physics!\n";
    accumulator += getDeltaTime();
    while(accumulator >= timeStep) {
        b2World_Step(worldId, timeStep, subStepCount);
        accumulator -= timeStep;
    }

    //update entities
    //cout << "updating entities!\n";
    for(Entity* entity : entities) {
        if (entity == nullptr) {
            continue;
        }

        //cout << "updating entity!\n";
        try {
            entity->update();
        } catch(const std::exception& e) {}
        
    }

    //log time:
    //cout << "deltaTime: " << std::to_string(getDeltaTime()) << "\n";
    //cout << "time: " << std::to_string(getTime()) << "\n";
}

void Game::destroy() {
    for(Entity* entity : entities) {
        try {
            entity->destroy();
        } catch(std::exception) {}
    }
    b2DestroyWorld(worldId);
}

std::vector<Entity*>* Game::getEntities() {
    return &entities;
}

float Game::getDeltaTime() {
    return deltaTime.count();
}

float Game::getTime() {
    return chrono::duration_cast<chrono::duration<float>>(time - initialTime).count();
}

b2WorldDef* Game::getWorldDef() {
    return &worldDef;
}

b2WorldId* Game::getWorldId() {
    return &worldId;
}

vector<int> Game::worldToScreen(b2Vec2 position) {
    return {
        static_cast<int>((position.x) * pixelsPerMeter) + zeroX,
        static_cast<int>((position.y) * pixelsPerMeter * -1.0f) + zeroY,
    };
}

b2Vec2 Game::screenToWorld(vector<int> position) {
    b2Vec2 vec2;
    vec2.x = static_cast<float>(position[0] - zeroX) / pixelsPerMeter;
    vec2.y = static_cast<float>(position[1] - zeroY) / pixelsPerMeter * -1;
    return vec2;

}

sf::RenderWindow* Game::getWindow() {
    return window;
}