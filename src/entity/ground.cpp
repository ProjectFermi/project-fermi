#include "ground.h"

#include "platform/platform.h"
#include "gameengine/gameengine.h"
#include "platform/graphicsscene.h"
#include <QGraphicsPixmapItem>

Ground::Ground(GameEngine *engine, const b2Vec2 &position, double width, double height) :
    Entity(engine)
{
    m_bodyDef = new b2BodyDef();
    m_bodyDef->position = position;
    m_body = m_world->CreateBody(m_bodyDef);
    m_polygonShape = new b2PolygonShape();
    m_shape = m_polygonShape;
    m_width = width;
    m_height = height;
    m_polygonShape->SetAsBox(m_width / 2, m_height / 2);
    m_body->CreateFixture(m_shape, 0.0);

    QPixmap pixmap(":/images/box.png");
    m_boxPixmap = new QGraphicsPixmapItem(pixmap, 0, m_engine->graphicsScene());
    m_boxPixmap->setVisible(false);
}

void Ground::updateGraphics() {
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
