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
  constexpr explicit NotePack(const rapidjson::GenericArray<Const, T> & jsonArray) {
    std::transform(jsonArray.Begin(), jsonArray.End(), std::back_inserter(m_notes),
                   [](const auto & jsonVal) {
                     Note ret{};
                     ret.time = jsonVal["_time"].GetFloat();
                     ret.direction = jsonVal["_direction"].GetUint();
                     ret.type = jsonVal["_type"].GetUint();
                     ret.line_idx = jsonVal["_lineIndex"].GetUint();
                     ret.column_idx = jsonVal["_columnIndex"].GetUint();
                     return ret;
                   });
  }
  NotePack(NotePack &&) = default;
  NotePack &operator=(NotePack &&) = default;

  [[nodiscard]] Note operator[](std::size_t i) const noexcept {
    return m_notes[i];
  }
};
