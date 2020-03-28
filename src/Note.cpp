//
// Created by hugo on 3/7/20.
//
#include "Note.hpp"

Note::Note(float time, int line_index, int column_index, Note::Type type, Note::Direction direction)
    : _time(time), _lineIndex(line_index), _columnIndex(column_index), _type(type), _direction(direction) {}
Note::Direction Note::direction() const { return _direction; }
float Note::time() const { return _time; }
int Note::lineIndex() const { return _lineIndex; }
int Note::columnIndex() const { return _columnIndex; }
Note::Type Note::type() const { return _type; }
