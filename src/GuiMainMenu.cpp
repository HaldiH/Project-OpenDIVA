//
// Created by hugo on 23.02.20.
//
#include "OpenDIVA/Gui/GuiMainMenu.hpp"
#include <QColor>
#include <QDebug>
#include <QKeyEvent>

GuiMainMenu::GuiMainMenu() {
    playButton->setHovered(true);
    playButton->setPos(width() / 2 - playButton->textWidth() / 2, 10);
    quitButton->setPos(width() / 2 - playButton->textWidth() / 2, 100);

    addItem(playButton);
    addItem(quitButton);
}

void GuiMainMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:

        break;
    case Qt::Key_Right:
        break;
    case Qt::Key_Up:
        playButton->setHovered(!playButton->isHovered());
        quitButton->setHovered(!playButton->isHovered());
        break;
    case Qt::Key_Down:
        playButton->setHovered(!playButton->isHovered());
        quitButton->setHovered(!playButton->isHovered());
        break;
    case Qt::Key_Enter:
        if (quitButton->isHovered())
            exit(0);
        if (playButton->isHovered())
            ;
        break;
    }
}
