//
// Created by hugo on 23.02.20.
//

#include "OpenDIVA/Gui/GuiButton.hpp"
GuiButton::GuiButton() {
    setAcceptHoverEvents(true);
    setAcceptTouchEvents(true);
}
bool GuiButton::isHovered() { return m_hover; }
GuiButton::GuiButton(const QString &text) { setPlainText(text); }
void GuiButton::setHovered(bool hover) {
    hover ? setDefaultTextColor(Qt::GlobalColor::red) : setDefaultTextColor(Qt::GlobalColor::white);
    m_hover = hover;
}
