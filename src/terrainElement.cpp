#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "terrainElement.h"
#include "entity.h"
#include "game.h"
#include "include/box2d/box2d.h"

using namespace std;

TerrainElement::TerrainElement(Game* game, float xPos, float yPos, float width, float height) : Entity(game) {
    name = "Terrain Element";
    this->width = width;
    this->height = height;
    position.x = xPos;
    position.y = yPos;
    rotation.c = 1;
    rotation.s = 0;
    initializePhysics(position, rotation);
    initializeGraphics();
}

TerrainElement::TerrainElement() {

}

void TerrainElement::update() {
    updateBase();  
}

void TerrainElement::destroy() {
    destroyBase();
}

void TerrainElement::initializePhysics(b2Vec2 position, b2Rot rotation) {
    initializePhysicsBase(position, rotation);
    bodyId = b2CreateBody(*worldId, &bodyDef);
    dynamicBox = b2MakeBox(0.5f * width, 0.5f * height);
    shapeDef = b2DefaultShapeDef();
    shapeDef.material.friction = friction;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void TerrainElement::initializeGraphics() {
    initializeGraphicsBase();
    drawEntity = true;
    graphicsType = "RectangleShape";
    rectangleShape = sf::RectangleShape({
        width * game->pixelsPerMeter, 
        height * game->pixelsPerMeter
    });
    rectangleShape.setFillColor(sf::Color(255, 255, 255));

}