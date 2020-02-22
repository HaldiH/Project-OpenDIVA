#ifndef MYRECT_H
#define MYRECT_H

#include "Type.hpp"
#include <QGraphicsRectItem>

class Note : public QGraphicsTextItem {
  public:
    enum Type { TARGET, HOLD_TARGET, SLIDER, CHAIN_SLIDER };

  private:
    double time;
    int lineIndex;
    int columnIndex;
};

#endif // MYRECT_H
