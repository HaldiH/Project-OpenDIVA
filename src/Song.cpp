//
// Created by hugo on 3/28/20.
//

#include "Song.hpp"
#include <fstream>
#include <rapidjson/istreamwrapper.h>

Song::Song(std::ifstream songInfoFile) {
    rapidjson::IStreamWrapper isw(songInfoFile);
    songInfo.ParseStream(isw);

    songName = songInfo["_songName"].GetString();
    bpm = songInfo["_beatsPerMinute"].GetFloat();
    audioFilename = songInfo["_audioFilename"].GetString();
    for (auto &json_difficulty_beat_map : songInfo["_difficultyBeatmapSet"].GetArray()) {
        Beatmap::Parameters beatmapParams;
        beatmapParams.beatmapFilename = json_difficulty_beat_map["_beatmapFilename"].GetString();
        beatmapParams.difficulty = Beatmap::Difficulty(json_difficulty_beat_map["_difficulty"].GetInt());
        beatmapParams.difficultyLabel = json_difficulty_beat_map["_difficultyLabel"].GetString();
        beatmapSet.push_back(beatmapParams);
    }

    new Beatmap(&beatmapSet.back(), bpm, 0);
}
