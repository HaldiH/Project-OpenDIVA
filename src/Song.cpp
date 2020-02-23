//
// Created by hugo on 22.02.20.
//

#include "OpenDIVA/Song.hpp"
#include <rapidjson/istreamwrapper.h>

Song::Song(std::ifstream songFile) {
    rapidjson::IStreamWrapper isw(songFile);

    json_document.ParseStream(isw);
    for (auto &json_note : json_document["_notes"].GetArray()) {
        notes.emplace_back(new Note(json_note["_time"].GetDouble(), json_note["_lineIndex"].GetInt(),
                                    json_note["_columnIndex"].GetInt(), Note::Type(json_note["_type"].GetInt()),
                                    Note::Direction(json_note["_direction"].GetInt())));
    }
}
