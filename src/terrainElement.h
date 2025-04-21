#include "entity.h"

class TerrainElement : public Entity {
    public:
        TerrainElement(Game* game, float xPos, float yPos, float width, float height);
        TerrainElement();
        void destroy();
        void update();
        void initializePhysics(b2Vec2 position, b2Rot rotation);
        void initializeGraphics();
    protected:
        b2Polygon dynamicBox;
        b2ShapeDef shapeDef;
        float density = 1.0f;
        float friction = 0.3f;

        

};