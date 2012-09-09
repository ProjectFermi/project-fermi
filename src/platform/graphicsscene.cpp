#include "graphicsscene.h"

#include "../gameengine/gameengine.h"

#include <iostream>
#include <QGraphicsSceneMouseEvent>

GraphicsScene::GraphicsScene(GameEngine *gameEngine) :
    QGraphicsScene(gameEngine),
    m_gameEngine(gameEngine)
{
    setSceneRect(0,0,400,400);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
    std::cout << "Mouse released at " << event->scenePos().x() << event->scenePos().y() << std::endl;
    m_gameEngine->onMouseReleased(event->scenePos().x(), event->scenePos().y());
}
