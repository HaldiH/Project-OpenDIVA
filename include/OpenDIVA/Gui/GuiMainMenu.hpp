//
// Created by hugo on 23.02.20.
//

#ifndef OPENDIVA_GUIMAINMENU_HPP
#define OPENDIVA_GUIMAINMENU_HPP

#include "Gui.hpp"
#include "GuiButton.hpp"
#include <QtWidgets/QGraphicsTextItem>

class GuiMainMenu : public Gui {
  public:
    GuiMainMenu();
    void keyPressEvent(QKeyEvent *event) override;

  private:
    GuiButton *playButton = new GuiButton("Play");
    GuiButton *quitButton = new GuiButton("Quit");

};

#endif // OPENDIVA_GUIMAINMENU_HPP
