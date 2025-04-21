#include <iostream>
#include <vector>


#include "entity.h"
#include "game.h"
#include "include/box2d/box2d.h"

using namespace std;

Entity::Entity(Game* game) {
    //cout << "initializing entity!\n";
    this->game = game;
    game->getEntities()->push_back(this);
}

Entity::Entity() {

}

void Entity::update() {
    updateBase();
}

void Entity::updateBase() {
    if(!game) {
        cout << "ERROR: game pointer is empty for this entity";
        return;
    }

    //update physics
    if(hasPhysics) {
        try {
            position = b2Body_GetPosition(bodyId);
            rotation = b2Body_GetRotation(bodyId);
        } catch(std::exception){}
    }

    //update graphics
    if(drawEntity) {
        vector<int> objectPosition = game->worldToScreen(position);
        if(graphicsType == "Sprite") {
            sprite.setPosition({
                static_cast<float>(objectPosition[0] - 0.5 * width * game->pixelsPerMeter), 
                static_cast<float>(objectPosition[1] - 0.5 * height * game->pixelsPerMeter)
            });
            window->draw(sprite);
        } else if(graphicsType == "RectangleShape") {
            rectangleShape.setPosition({
                static_cast<float>(objectPosition[0] - 0.5 * width * game->pixelsPerMeter), 
                static_cast<float>(objectPosition[1] - 0.5 * height * game->pixelsPerMeter)
            });
            window->draw(rectangleShape);
        } else if(graphicsType == "CirleShape") {
            circleShape.setPosition({
                static_cast<float>(objectPosition[0] - 0.5 * width * game->pixelsPerMeter), 
                static_cast<float>(objectPosition[1] - 0.5 * height * game->pixelsPerMeter)
            });
            window->draw(circleShape);
        } else if(graphicsType == "ConvexShape") {
            convexShape.setPosition({
                static_cast<float>(objectPosition[0] - 0.5 * width * game->pixelsPerMeter), 
                static_cast<float>(objectPosition[1] - 0.5 * height * game->pixelsPerMeter)
            });
            window->draw(convexShape);
        }
        
    }
}

void Entity::destroy() {
    destroyBase();
}

void Entity::destroyBase() {
    vector<Entity*>* entities = game->getEntities();
    if(hasPhysics) {
        destroyPhysics();
    }
}

void Entity::initializeGraphics() {

}

void Entity::initializeGraphicsBase() {
    window = game->getWindow();
    drawEntity = true;
}

void Entity::initializePhysics(b2Vec2 position, b2Rot rotation) {
    initializePhysicsBase(position, rotation);
    bodyId = b2CreateBody(*worldId, &bodyDef);
}

void Entity::initializePhysicsBase(b2Vec2 position, b2Rot rotation) {
    hasPhysics = true;
    worldDef = game->getWorldDef();
    worldId = game->getWorldId();
    bodyDef = b2DefaultBodyDef();
    bodyDef.position = position;
    bodyDef.rotation = rotation;
    this->position = bodyDef.position;
    this->rotation = bodyDef.rotation;
}

void Entity::destroyPhysics() {

}
