#include "ball.h"

#include "platform/platform.h"

Ball::Ball(GameEngine *engine) :
    Entity(engine)
{
    bodyDef = new b2BodyDef();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(4, 20);
    bodyDef->linearVelocity.y = 5;
    bodyDef->linearVelocity.x = 1;
    m_body = world->CreateBody(bodyDef);
    shape = new b2CircleShape();
    m_height = m_width = 0.5;
    shape->m_radius = m_height / 2;

    b2FixtureDef *fixtureDef = new b2FixtureDef();
    fixtureDef->shape = shape;
    fixtureDef->density = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->friction = 0.3f;

    m_body->CreateFixture(fixtureDef);
    m_sprite = platform->createSprite("..."); // TODO create real sprites
}
