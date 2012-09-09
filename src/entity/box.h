#ifndef BOX_H
#define BOX_H

#include "entity.h"
#include <QGraphicsPixmapItem>

class Box : public Entity
{
public:
    Box(GameEngine *gameEngine, const b2Vec2 &position, double width, double height);
    void updateGraphics();
protected:
    b2PolygonShape* polygonShape;
    QGraphicsPixmapItem *m_boxPixmap;
};

#endif // BOX_H
