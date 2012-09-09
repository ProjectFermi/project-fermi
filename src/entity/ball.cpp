#include "ball.h"

#include "platform/platform.h"
#include "gameengine/gameengine.h"
#include "platform/graphicsscene.h"

#include <QDebug>

Ball::Ball(GameEngine *engine, const b2Vec2 &position, double radius) :
    Entity(engine)
{
    m_bodyDef = new b2BodyDef();
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->position = position;
    m_body = m_world->CreateBody(m_bodyDef);
    m_shape = new b2CircleShape();
    m_height = m_width = radius * 2;
    m_shape->m_radius = radius;

    b2FixtureDef *fixtureDef = new b2FixtureDef();
    fixtureDef->shape = m_shape;
    fixtureDef->density = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->friction = 0.3f;

    m_body->CreateFixture(fixtureDef);
    QPixmap pixmap(":/images/ball.png");
    m_ballPixmap = new QGraphicsPixmapItem(pixmap, 0, m_engine->graphicsScene());
    m_ballPixmap->setVisible(false);
//    m_ballPixmap->setScale(1);
}

void Ball::updateGraphics() {
    double scale = m_engine->scale();
    double x = m_body->GetPosition().x * scale;
    double y = m_body->GetPosition().y * scale;
    double width = m_width * scale;
    double rotation = m_body->GetAngle();
    QPixmap tmpPixmap = m_ballPixmap->pixmap();
    m_ballPixmap->setPixmap(tmpPixmap.scaledToWidth(width, Qt::SmoothTransformation));
    m_ballPixmap->setTransformOriginPoint(width/2, width/2);
    m_ballPixmap->setRotation(rotation * 180 / M_PI);
    m_ballPixmap->setPos(-width/2 + x, -width/2 + y);
    m_ballPixmap->setVisible(true);
}
