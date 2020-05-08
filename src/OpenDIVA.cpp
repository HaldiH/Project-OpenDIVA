//
// Created by hugo on 4/24/20.
//

#include "OpenDIVA.hpp"
#include "Beatmap.hpp"
#include "Level.hpp"

OpenDIVA::OpenDIVA() {}

int main(int argc, char* argv[]) {
    Level level("song_info.json");
    level.Test();
}