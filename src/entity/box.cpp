#include "box.h"

#include "platform/platform.h"
#include "gameengine/gameengine.h"
#include "platform/graphicsscene.h"
#include <QGraphicsPixmapItem>

Box::Box(GameEngine *engine, const b2Vec2 &position, double width, double height) :
    Entity(engine)
{
    m_bodyDef = new b2BodyDef();
    m_bodyDef->type = b2_dynamicBody;
    m_bodyDef->position = position;
    m_body = m_world->CreateBody(m_bodyDef);

    polygonShape = new b2PolygonShape();
    m_width = width;
    m_height = height;
    polygonShape->SetAsBox(m_width / 2, m_height / 2);
    m_shape = polygonShape;

    b2FixtureDef *fixtureDef = new b2FixtureDef();
    fixtureDef->shape = m_shape;
    fixtureDef->density = 1.0f;
    fixtureDef->restitution = 0.4f;
    fixtureDef->friction = 0.3f;

    m_body->CreateFixture(fixtureDef);
    m_body->SetAngularVelocity(0.1);

    QPixmap pixmap(":/images/box.png");
    m_boxPixmap = new QGraphicsPixmapItem(pixmap, 0, m_engine->graphicsScene());
    m_boxPixmap->setVisible(false);
}

void Box::updateGraphics() {
    double scale = m_engine->scale();
    double x = m_body->GetPosition().x * scale;
    double y = m_body->GetPosition().y * scale;
    double width = m_width * scale;
    double rotation = m_body->GetAngle();
    QPixmap tmpPixmap = m_boxPixmap->pixmap();
    m_boxPixmap->setPixmap(tmpPixmap.scaledToWidth(width, Qt::SmoothTransformation));
    m_boxPixmap->setTransformOriginPoint(width/2, width/2);
    m_boxPixmap->setRotation(rotation * 180 / M_PI);
    m_boxPixmap->setPos(-width/2 + x, -width/2 + y);
    m_boxPixmap->setVisible(true);
}
