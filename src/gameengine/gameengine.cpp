#include "gameengine.h"

#include "macros.h"

// Qt includes
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGLWidget>
#include <QDebug>

// Box2D includes
#include <Box2D.h>

// STL includes
#include <iostream>

// Local includes
#include "platform/platform.h"
#include "entity/ball.h"
#include "entity/ground.h"
#include "entity/box.h"
#include "platform/graphicsscene.h"

using std::cout;
using std::endl;

/*!
  The GameEngine class contains all the logic to run the game or testbed.
  It also works as an interface between the Platform and Box2D.
  */
/*
    Developer notes: Divide this class into reasonable modules in as great an
    extent as possible. The main class in a game engine tends to get quite bloaty
    in time. Putting things in modules from the beginning should make it easier to
    maintain (and quicker to compile).
*/
GameEngine::GameEngine(int argc, char *argv[]) :
    QObject(),
    m_scale(10),
    m_timeStep(1/60.)
{
    (void)argc;
    (void)argv;
    m_engineMode = ModeTestbed;
    m_gameState = GameStarted;

    // Graphics view
    m_graphicsView = new QGraphicsView();
    m_graphicsView->setRenderHint(QPainter::HighQualityAntialiasing,true);
    m_graphicsView->setRenderHint(QPainter::SmoothPixmapTransform,true);
    QGLWidget *glwidget = new QGLWidget(m_graphicsView);
    m_graphicsView->setViewport(glwidget);
    m_graphicsView->scale(1,-1);

    // Graphics scene
    m_graphicsScene = new GraphicsScene(this);
    m_graphicsScene->setSceneRect(0,0,800,480);
    m_graphicsView->setScene(m_graphicsScene);

    // Timer
    m_stepTimer = new QTimer();
    connect(m_stepTimer, SIGNAL(timeout()), SLOT(advance()));
    initBox2D();
}

GameEngine::~GameEngine() {
    delete m_graphicsView;
}

void GameEngine::initBox2D() {
    std::cout << "initBox2D called" << std::endl;

    m_stepTimer->setInterval(m_timeStep);
    m_stepTimer->stop();

    b2Vec2 gravity(0,-1.81);
    m_world = new b2World(gravity);
    if(engineMode() == ModeTestbed) {
        Ground *ground = new Ground(this, b2Vec2(0,10), 10, 10);
        entities.push_back(ground);
        Ground *ground2 = new Ground(this, b2Vec2(10,10), 10, 10);
        entities.push_back(ground2);
        Ground *ground3 = new Ground(this, b2Vec2(20,10), 10, 10);
        entities.push_back(ground3);
        Ground *ground4 = new Ground(this, b2Vec2(30,10), 10, 10);
        entities.push_back(ground4);
        Box *box = new Box(this, b2Vec2(10,20), 5, 5);
        box->body()->SetLinearVelocity(b2Vec2(2,2));
        entities.push_back(box);
        Ball *ball = new Ball(this, b2Vec2(15,30),2);
        ball->body()->SetLinearVelocity(b2Vec2(1,2));
        entities.push_back(ball);
    } else {
        std::cerr << "Mode not implemented!" << std::endl;
    }
}

void GameEngine::redraw() {
//    graphicsScene->clear();
    for(uint i = 0; i < entities.size(); i++) {
        Entity* entity = entities.at(i);
//        m_scale = 10;
//        // scaling should be redone
//        double x = entity->body()->GetPosition().x * m_scale;
//        double y = entity->body()->GetPosition().y * m_scale;
//        double width = entity->width() * m_scale;
//        double height = entity->height() * m_scale;
//        platform()->drawSprite(entity->sprite(), x, y, width, height, entity->body()->GetAngle());
        entity->updateGraphics();
    }
    m_graphicsScene->update();
}

void GameEngine::advance() {
    int velocityIterations = 6;
    int positionIterations = 2;

    m_world->Step(m_timeStep, velocityIterations, positionIterations);
    redraw();
}

void GameEngine::startGame() {
    m_gameState = GameRunning;
    m_stepTimer->start();
}

void GameEngine::start()
{
    m_graphicsView->show();

    startGame();
}

void GameEngine::onMouseReleased(int x, int y) {
    cout << b2Vec2(x,y).x << " " << b2Vec2(x,y).y << endl;
    b2Vec2 position;
    position.x = x / m_scale;
    position.y = y / m_scale;
    Ball *ball = new Ball(this, position, 2);
    ball->body()->SetLinearVelocity(b2Vec2(0,0));
    entities.push_back(ball);
}
