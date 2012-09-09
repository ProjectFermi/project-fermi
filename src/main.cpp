#include <iostream>
#include <QApplication>

#include "gameengine/gameengine.h"
/*!
  The main file loads the platform which sets up everything it needs.
*/
int main(int argc, char* argv[]) {
    QApplication qtApp(argc, argv);
    GameEngine gameEngine(argc, argv);
    gameEngine.start();
    return qtApp.exec();
}
