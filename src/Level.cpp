//
// Created by hugo on 4/25/20.
//

#include "Level.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

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
        difficultyBeatmapParamsSet.push_back(
            {std::string(jsonBeatmap["_beatmapFilename"].GetString()),
             jsonBeatmap["_difficultyLabel"].GetString(),
             Beatmap::Difficulty(jsonBeatmap["_difficulty"].GetInt())});
    }
}

void Level::Test() {
    std::cout << "version: " << version << std::endl;
    std::cout << "Song name: " << songName << std::endl;
    std::cout << "BPM: " << beatsPerMinute << std::endl;
    std::cout << "Audio filename: " << audioFilename << std::endl;
    std::cout << "Contains the following beatmap: " << std::endl;
    for (auto& beatmapParamsSet : difficultyBeatmapParamsSet) {
        std::cout << "\tLabel: " << beatmapParamsSet.difficultyLabel << std::endl;
        std::cout << "\tDifficulty: " << int(beatmapParamsSet.difficulty) << std::endl;
        std::cout << "\tBeatmap filename: " << beatmapParamsSet.beatmapFilename << std::endl;
        std::cout << "\t------" << std::endl;
    }
    auto testingBeatmap = difficultyBeatmapParamsSet[0];
    Beatmap beatmap(testingBeatmap.beatmapFilename, testingBeatmap.difficulty,
                    testingBeatmap.difficultyLabel);
    beatmap.OnExecute();
}
