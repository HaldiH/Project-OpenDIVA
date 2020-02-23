//
// Created by hugo on 22.02.20.
//

#ifndef OPENDIVA_SONG_HPP
#define OPENDIVA_SONG_HPP

#include "Note.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <vector>

class Song {
  public:
    explicit Song(std::ifstream songFile);

  private:
    rapidjson::Document json_document;
    std::vector<Note *> notes;
};

#endif // OPENDIVA_SONG_HPP
