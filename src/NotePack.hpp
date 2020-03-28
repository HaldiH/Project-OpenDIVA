//
// Created by AeroStun on 3/20/20.
//

#pragma once

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <rapidjson/document.h>
#include <vector>

struct NotePack {
  static_assert(sizeof(float) == 4);
  struct Note {
    float time;
    std::uint32_t direction : 2;
    std::uint32_t type : 2;

  private:
    std::uint32_t padding_line : 2;

  public:
    std::uint32_t line_idx : 10;

  private:
    std::uint32_t padding_col : 6;

  public:
    std::uint32_t column_idx : 10;
  };
  static_assert(sizeof(Note) == 8);

private:
  std::vector<Note> m_notes;

public:
  template <bool Const, class T>
  constexpr explicit NotePack(const rapidjson::GenericArray<Const, T> &jarray) {
    std::transform(jarray.Begin(), jarray.End(), std::back_inserter(m_notes),
                   [](const auto &jval) {
                     Note ret{};
                     ret.time = jval["_time"].GetFloat();
                     ret.direction = jval["_direction"].GetUint();
                     ret.type = jval["_type"].GetUint();
                     ret.line_idx = jval["_lineIdx"].GetUint();
                     ret.column_idx = jval["_columnIdx"].GetUint();
                     return ret;
                   });
  }
  NotePack(NotePack &&) = default;
  NotePack &operator=(NotePack &&) = default;

  [[nodiscard]] Note operator[](std::size_t i) const noexcept {
    return m_notes[i];
  }
};
