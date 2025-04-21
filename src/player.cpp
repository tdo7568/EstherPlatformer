#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "player.h"
#include "entity.h"
#include "game.h"
#include "include/box2d/box2d.h"

using namespace std;

Player::Player(Game* game, float xPos, float yPos) : Entity(game) {
    name = "Player";
    width = 1.0f;
    height = 1.0f;
    position.x = xPos;
    position.y = yPos;
    rotation.c = 1;
    rotation.s = 0;
    initializePhysics(position, rotation);
    initializeGraphics();
}

Player::Player() {

}

void Player::update() {
    //calculate input vector
    bool inputKey = false;
    b2Vec2 inputVector;
    inputVector.x = 0;
    inputVector.y = 0;
    b2Vec2 zero = inputVector;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if(upKey == false) {
            inputVector.y = inputVector.y + 1;
        }
        upKey = true;
        inputKey = true;
    } else {
        upKey = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(downKey == false) {
            inputVector.y = inputVector.y - 1;
        }
        downKey = true;
        inputKey = true;
    } else {
        downKey = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(leftKey == false) {
            inputVector.x = inputVector.x - 1;
        }
        leftKey = true;
        inputKey = true;
    } else {
        leftKey = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if(rightKey == false) {
            inputVector.x = inputVector.x + 1;
        }
        rightKey = true;
        inputKey = true;
    } else {
        rightKey = false;
    }
    if(inputVector.x != 0.0f || inputVector.y != 0.0f) {
        float length = std::sqrt(inputVector.x * inputVector.x + inputVector.y * inputVector.y);
        inputVector.x = inputVector.x / length * inputForce;
        inputVector.y = 1.5f * inputVector.y / length * inputForce;
    }
    if(inputKey) {
        
        b2Body_ApplyLinearImpulseToCenter(bodyId, inputVector, true);
    }

    //cout << "updating player\n";
    updateBase();
    
    //log position
    //cout << "Position: (" << position.x << ", " << position.y << ")\n";
    //cout << "Velocity: (" << b2Body_GetLinearVelocity(bodyId).x << ", " << b2Body_GetLinearVelocity(bodyId).y << ")\n";
}

void Player::destroy() {
    destroyBase();
}

void Player::initializePhysics(b2Vec2 position, b2Rot rotation) {
    initializePhysicsBase(position, rotation);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyId = b2CreateBody(*worldId, &bodyDef);
    dynamicBox = b2MakeBox(0.5f * width, 0.5f * height);
    shapeDef = b2DefaultShapeDef();
    shapeDef.density = density;
    shapeDef.material.friction = friction;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void Player::initializeGraphics() {
    initializeGraphicsBase();
    drawEntity = true;
    graphicsType = "RectangleShape";
    rectangleShape = sf::RectangleShape({
        width * game->pixelsPerMeter, 
        height * game->pixelsPerMeter
    });
    rectangleShape.setFillColor(sf::Color(255, 0, 0));

}