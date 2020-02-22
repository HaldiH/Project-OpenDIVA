//
// Created by hugo on 22.02.20.
//

#ifndef OPENDIVA_GUI_HPP
#define OPENDIVA_GUI_HPP

#include <QGraphicsScene>

class Gui : public QGraphicsScene {
  public:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // OPENDIVA_GUI_HPP
