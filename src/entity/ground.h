#ifndef GROUND_H
#define GROUND_H

#include "entity.h"
#include <QGraphicsPixmapItem>

class Ground : public Entity
{
public:
    Ground(GameEngine *m_engine, const b2Vec2 &position, double width, double height);
    void updateGraphics();
private:
    b2PolygonShape* m_polygonShape;
    QGraphicsPixmapItem *m_boxPixmap;
};

#endif // GROUND_H
