#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "platform/platform.h"
#include "entity/entity.h"

#include <Box2D.h>
#include <vector>

// Qt includes
#include <QObject>
#include <QTimer>
#include <QGraphicsView>

// Forward declarations
class GraphicsScene;

class GameEngine : public QObject
{
    Q_OBJECT
public:
    GameEngine(int argc, char *argv[]);

    enum GameState{
        GameStarted, /*! The game has just started */
        GameRunning, /*! The game is running */
        GamePaused,  /*! The game has been paused */
        GameOver,    /*! The level was failed */
        GameInstructionPause /*! The game is running, but we are showing instructions on screen */
    };

    enum EngineMode {
        ModeGame, /*! The engine is running as a regular game */
        ModeTestbed /*! The engine is running in testbed mode */
    };

    GameState gameState() {
        return m_gameState;
    }

    EngineMode engineMode() {
        return m_engineMode;
    }

    void initBox2D();
    void start();
    void redraw();
    b2World *world() {
        return m_world;
    }

    void onMouseReleased(int x, int y);


    QGraphicsView *graphicsView() {
        return m_graphicsView;
    }
    GraphicsScene *graphicsScene() {
        return m_graphicsScene;
    }
    double scale() {
        return m_scale;
    }

    void startGame();
    ~GameEngine();
public slots:
    void advance();

protected:
    EngineMode m_engineMode;
    GameState m_gameState;

    b2World *m_world;

    std::vector<Entity*> entities;

    double m_scale;

    QTimer *m_stepTimer;
    double m_timeStep;

    QGraphicsView *m_graphicsView;
    GraphicsScene *m_graphicsScene;
};

#endif // GAMEENGINE_H
