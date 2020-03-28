#pragma once

#include <QGraphicsRectItem>

class Note {
  public:
    enum Type { TARGET, HOLD_TARGET, SLIDER, CHAIN_SLIDER };
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Note(float time, int line_index, int column_index, Type type, Direction direction);
    [[nodiscard]] Direction direction() const;
    [[nodiscard]] float time() const;
    [[nodiscard]] int lineIndex() const;
    [[nodiscard]] int columnIndex() const;
    [[nodiscard]] Type type() const;

  private:
    float _time;
    int _lineIndex;
    int _columnIndex;
    Type _type;
    Direction _direction;
};
