#include "entity.h"

class Player : public Entity {
    public:
        Player(Game* game, float xPos, float yPos);
        Player();
        void destroy();
        void update();
        void initializePhysics(b2Vec2 position, b2Rot rotation);
        void initializeGraphics();
    protected:
        b2Polygon dynamicBox;
        b2ShapeDef shapeDef;
        float density = 4.0f;
        float friction = 0.3f;
        float inputForce = 50.0f;
        bool upKey = false;
        bool downKey = false;
        bool leftKey = false;
        bool rightKey = false;

        

};