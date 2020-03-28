//
// Created by hugo on 3/28/20.
//

#include "Beatmap.hpp"
#include <QDebug>
#include <QTimer>
#include <deque>
#include <fstream>
#include <rapidjson/istreamwrapper.h>

Beatmap::Beatmap(Beatmap::Parameters *params, float bpm, float offset)
    : _params(params), time(offset), interval(60 / bpm / 128) { // 128 intervals per beat
    std::ifstream ifs(std::string(_params->beatmapFilename));
    rapidjson::IStreamWrapper isw(ifs);
    json_beatmap.ParseStream(isw);
    for (auto &json_note : json_beatmap["_notes"].GetArray()) {
        noteSet.emplace(Note(json_note["_time"].GetFloat(), json_note["_lineIndex"].GetInt(),
                             json_note["_columnIndex"].GetInt(), Note::Type(json_note["_type"].GetInt()),
                             Note::Direction(json_note["_direction"].GetInt())));
    }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(playNotes()));
    timer->start(qRound(interval * 1000));
}

void Beatmap::playNotes() {
    if (!noteSet.empty()) {
        if (const auto &note = noteSet.front(); note.time() <= time) {
            qDebug() << "Note: " << note.time();
            noteSet.pop();
        }
    }
    time += interval;
}

Beatmap::~Beatmap() {
    timer->stop();
    delete(timer);
}
