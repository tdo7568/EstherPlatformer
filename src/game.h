#pragma once

#include <chrono>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "include/box2d/box2d.h"
#include "entity.h"

using namespace std;

class Game {
    public:
        Game(sf::RenderWindow *window, int width, int height, int zeroX, int zeroY);
        Game();
        void update();
        void destroy();
        float getDeltaTime();
        float getTime();
        void drawEntity();
        std::vector<Entity*>* getEntities();
        b2WorldDef* getWorldDef();
        b2WorldId* getWorldId();
        vector<int> worldToScreen(b2Vec2 position);
        b2Vec2 screenToWorld(vector<int> position);
        sf::RenderWindow* getWindow();
        float pixelsPerMeter = 50;

    private:
        sf::RenderWindow *window;
        int windowWidth = 0;
        int windowHeight = 0;
        int zeroX = 0;
        int zeroY = 0;
        b2WorldDef worldDef;
        b2WorldId worldId;
        float gravity = -20.0f;
        std::vector<Entity*> entities;
        float timeStep = 1.0f / 60.0f;
        int subStepCount = 4;
        std::chrono::high_resolution_clock::time_point initialTime;
        std::chrono::high_resolution_clock::time_point time;
        std::chrono::high_resolution_clock::time_point lastTime;
        std::chrono::duration<float> deltaTime;
        float accumulator;


};