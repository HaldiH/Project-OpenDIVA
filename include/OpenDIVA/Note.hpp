#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>

class Note {
  public:
    enum Type { TARGET, HOLD_TARGET, SLIDER, CHAIN_SLIDER };
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Note(double time, int line_index, int column_index, Type type, Direction direction)
        : m_time(time), m_lineIndex(line_index), m_columnIndex(column_index), m_type(type), m_direction(direction){};

  private:
    double m_time;
    int m_lineIndex;
    int m_columnIndex;
    Type m_type;
    Direction m_direction;
};

#endif // MYRECT_H
