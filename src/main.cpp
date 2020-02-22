#include "OpenDIVA/Note.hpp"
#include "OpenDIVA/Gui.hpp"
#include "OpenDIVA/SongLoader.hpp"
#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto scene = new Gui();

    scene->setFocus();

    auto view = new QGraphicsView(scene);
    view->show();

    return a.exec();
}
