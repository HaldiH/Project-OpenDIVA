//
// Created by hugo on 4/25/20.
//

#include "Level.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <utility>

Level::Level(const std::string& levelFile) {
    std::ifstream ifs(levelFile);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document jsonLevel;
    jsonLevel.ParseStream(isw);

    version = jsonLevel["_version"].GetString();
    songName = jsonLevel["_songName"].GetString();
    beatsPerMinute = jsonLevel["_beatsPerMinute"].GetFloat();
    audioFilename = jsonLevel["_audioFilename"].GetString();
    for (auto& jsonBeatmap : jsonLevel["_difficultyBeatmapSet"].GetArray()) {
        difficultyBeatmapSet.emplace_back(BeatmapParams(
            std::string(jsonBeatmap["_beatmapFilename"].GetString()),
            jsonBeatmap["_difficultyLabel"].GetString(),
            Difficulty(jsonBeatmap["_difficulty"].GetInt())));
    }
}

void Level::Test() {
    std::cout << "version: " << version << std::endl;
    std::cout << "Song name: " << songName << std::endl;
    std::cout << "BPM: " << beatsPerMinute << std::endl;
    std::cout << "Audio filename: " << audioFilename << std::endl;
    std::cout << "Contains the following beatmap: " << std::endl;
    for (auto& beatmap : difficultyBeatmapSet) {
        std::cout << "\tLabel: " << beatmap._difficultyLabel << std::endl;
        std::cout << "\tDifficulty: " << int(beatmap._difficulty) << std::endl;
        std::cout << "\tBeatmap filename: " << beatmap._beatmapFilename
                  << std::endl;
        std::cout << "\t------" << std::endl;
    }
    Beatmap beatmap(difficultyBeatmapSet[0]);
    beatmap.OnExecute();
}
