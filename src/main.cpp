#include "OpenDIVA/Gui/Gui.hpp"
#include "OpenDIVA/Song.hpp"
#include <OpenDIVA/Gui/GuiMainMenu.hpp>
#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto scene = new GuiMainMenu();

    scene->setFocus();

    auto view = new QGraphicsView(scene);
    view->show();
    Song song(std::ifstream("test.json"));

    return QApplication::exec();
}
