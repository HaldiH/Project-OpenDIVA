//
// Created by hugo on 4/24/20.
//

#include "Beatmap.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <utility>

Note::Note(int line_index, int column_index, Note::Type type, Note::Direction direction)
    : _lineIndex(line_index), _columnIndex(column_index), _type(type), _direction(direction) {}
Note::Direction Note::direction() const { return _direction; }
int Note::lineIndex() const { return _lineIndex; }
int Note::columnIndex() const { return _columnIndex; }
Note::Type Note::type() const { return _type; }

NoteTime::NoteTime(Note note, float time) : time(time), size(1) { notes.emplace_back(note); }
void NoteTime::AddNote(Note note) {
    notes.emplace_back(note);
    size++;
}

BeatmapParams::BeatmapParams(std::string beatmapFilename, std::string difficultyLabel,
                             Difficulty difficulty)
    : _beatmapFilename(std::move(beatmapFilename)), _difficultyLabel(std::move(difficultyLabel)),
      _difficulty(difficulty) {}

Beatmap::Beatmap(BeatmapParams params)
    : params(std::move(params)), spriteSheet("../res/arrow.bmp", 3, 3) {}

bool Beatmap::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!(window = SDL_CreateWindow("Project OpenDIVA", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return false;
    }

    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
        return false;
    }

    tp1 = tp0 = std::chrono::system_clock::now();

    std::cout << "Starting a beatmap: " << params._difficultyLabel << std::endl;

    std::ifstream ifs(params._beatmapFilename);
    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document jsonBeatmap;
    jsonBeatmap.ParseStream(isw);
    for (auto& json_note : jsonBeatmap["_notes"].GetArray()) {
        auto time = json_note["_time"].GetFloat();
        const auto note = Note(json_note["_lineIndex"].GetInt(), json_note["_columnIndex"].GetInt(),
                               Note::Type(json_note["_type"].GetInt()),
                               Note::Direction(json_note["_direction"].GetInt()));
        NoteTime* lastNoteTime;
        if (!noteSet.empty() && (lastNoteTime = &noteSet.back())->time == time) {
            lastNoteTime->AddNote(note);
        } else {
            noteSet.emplace(NoteTime(note, time));
        }
    }
    return bRunning = true;
}

void Beatmap::OnEvent(SDL_Event* event) {
    switch (event->type) {
    case SDL_QUIT:
        bRunning = false;
        break;
    case SDL_KEYDOWN:
        auto key_pressed = event->key.keysym.sym;
        std::cout << "Key pressed" << std::endl;
        if (key_pressed == SDLK_F11) {
            if (bFullScreen)
                SDL_SetWindowFullscreen(window, 0);
            else
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        }
    }
}

void Beatmap::OnLoop() {
    std::chrono::time_point<std::chrono::system_clock> tp2 = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedTime = tp2 - tp0;
    std::chrono::duration<float> delta = tp2 - tp1;

    auto* front = &noteSet.front();
    if (front->time > elapsedTime.count()) {
        //            std::cout << noteSet.front().time() -
        //            elapsedTime.count()
        //                      << std::endl;
    } else {
        std::cout << "New NoteTime containing " << int(front->size) << " notes" << std::endl;
        noteSet.pop();
        if (noteSet.empty())
            bRunning = false;
    }

    if (delta.count() >= 0.05) {
        tp1 = std::chrono::system_clock::now();
    }
}

void Beatmap::OnRender() {
    SDL_Surface* surf = SDL_GetWindowSurface(window);
    if (!surf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        bRunning = false;
        return;
    }

    uint sprite_n;
    if (noteSet.empty())
        return;
    for (const auto& note : noteSet.front().notes) {
        switch (note.direction()) {
        case Note::UP:
            sprite_n = 4;
            break;
        case Note::DOWN:
            sprite_n = 5;
            break;
        case Note::LEFT:
            sprite_n = 6;
            break;
        case Note::RIGHT:
            sprite_n = 7;
            break;
        }

        spriteSheet.Draw(surf, sprite_n, (int)(note.columnIndex() * surf->w / 3),
                         (int)(note.lineIndex() * surf->h / 3));
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void Beatmap::OnCleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Beatmap::OnExecute() {
    if (!OnInit()) {
        return false;
    }
    SDL_Event event;
    while (bRunning) {
        while (SDL_PollEvent(&event)) {
            OnEvent(&event);
        }
        OnLoop();
        OnRender();
    }
    OnCleanup();
    return true;
}
