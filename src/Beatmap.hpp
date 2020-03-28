//
// Created by hugo on 3/28/20.
//

#pragma once

#include "Note.hpp"
#include <QObject>
#include <QTimer>
#include <queue>
#include <rapidjson/document.h>
#include <string>

class Beatmap : public QObject {
    friend class Song;
    Q_OBJECT

  public:
    enum Difficulty { EASY, NORMAL, HARD, EXPERT, EXPERT_PLUS };

  private:
    struct Parameters {
        Difficulty difficulty;
        std::string_view beatmapFilename;
        std::string_view difficultyLabel;
    };
    rapidjson::Document json_beatmap;
    std::queue<Note> noteSet;
    Parameters *_params;
    float time;
    float interval;
    QTimer *timer;

  public:
    Beatmap(Beatmap::Parameters *params, float bpm, float offset);
    ~Beatmap() override;

  public slots:
    void playNotes();
};