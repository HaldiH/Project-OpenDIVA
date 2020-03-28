//
// Created by hugo on 3/15/20.
//

#include "Game.hpp"
#include "Song.hpp"
#include <fstream>

Game::Game() {
    auto test = new Song(std::ifstream("song_info.json"));
}
