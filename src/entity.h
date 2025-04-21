#pragma once

#include <vector>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "include/box2d/box2d.h"

class Game;

class Entity {
    public:
        Entity(Game* game); 
        Entity();
        std::vector<double> getPosition();
        virtual void destroy();
        virtual void update();
        virtual void initializePhysics(b2Vec2 position, b2Rot rotation);
        virtual void initializeGraphics();
        void destroyPhysics();
        void destroyBase();
        void updateBase();
        void initializePhysicsBase(b2Vec2 position, b2Rot rotation);
        void initializeGraphicsBase();

    protected:
        Game* game = nullptr;
        std::string name;
        double x;
        double y;
        double z;
        float width;
        float height;
        bool drawEntity = false;
        bool hasPhysics = false;
        b2WorldDef* worldDef;
        b2WorldId* worldId;
        b2BodyDef bodyDef;
        b2BodyId bodyId;
        b2Vec2 position;
        b2Rot rotation;
        std::string graphicsType;
        sf::RenderWindow* window;
        sf::Sprite sprite;
        sf::RectangleShape rectangleShape;
        sf::CircleShape circleShape;
        sf::ConvexShape convexShape;
};
