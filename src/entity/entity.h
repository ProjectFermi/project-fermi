#ifndef ENTITY_H
#define ENTITY_H

class GameEngine;
class Platform;
class Sprite;
#include <Box2D.h>

// Qt includes
#include <QGraphicsItem>

class Entity
{
public:
    Entity(GameEngine *m_engine);

    b2Body *body() {
        return m_body;
    }

    double width() {
        return m_width;
    }

    double height() {
        return m_height;
    }

    // TODO check that this is assigned a fixtureDef
    b2FixtureDef *fixtureDef() {
        return m_fixtureDef;
    }

    virtual void updateGraphics() {

    }

protected:
    GameEngine *m_engine;
    b2World *m_world;
    b2BodyDef *m_bodyDef;
    b2Body *m_body;
    b2Shape *m_shape;
    b2FixtureDef *m_fixtureDef;

    double m_width;
    double m_height;
};

#endif // ENTITY_H
