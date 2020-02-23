//
// Created by hugo on 23.02.20.
//

#ifndef OPENDIVA_GUIBUTTON_HPP
#define OPENDIVA_GUIBUTTON_HPP

#include <QtWidgets/QGraphicsItem>

class GuiButton : public QGraphicsTextItem {
  public:
    GuiButton();
    ~GuiButton() override = default;
    explicit GuiButton(const QString &text);
    bool isHovered();
    void setHovered(bool hover);

  private:
    bool m_hover = false;
};

#endif // OPENDIVA_GUIBUTTON_HPP
