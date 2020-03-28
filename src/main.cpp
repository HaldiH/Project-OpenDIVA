#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <fstream>
#include "Game.hpp"

/*
Tutorial Topics:
-QTimer
-signals and slots (connect function)
-QObject and Q_OBJECT macro
*/

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto *scene = new Game();

    // create a view to visualize the scene
    auto *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // show the view
    view->show();

    //==new code==


    return QApplication::exec();
}