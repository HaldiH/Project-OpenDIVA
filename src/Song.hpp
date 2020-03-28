//
// Created by hugo on 3/28/20.
//

#pragma once

#include "Beatmap.hpp"
#include <rapidjson/document.h>
#include <vector>

class Song {
  private:
    rapidjson::Document songInfo;
    std::vector<Beatmap::Parameters> beatmapSet;
    std::string audioFilename;
    std::string songName;
    float bpm;

  public:
    explicit Song(std::ifstream songInfoFile);
    ~Song() = default;
};
