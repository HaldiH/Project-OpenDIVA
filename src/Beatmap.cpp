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
Note::Note(Note::Type type, Note::Direction direction)
    : _type(type), _direction(direction), _lineIndex(0), _columnIndex(0) {}
bool Note::operator==(Note note) { return _type == note.type() && _direction == note.direction(); }

Beatmap::NoteTime::NoteTime(Note note, float time) : time(time) { notes.emplace_back(note); }
void Beatmap::NoteTime::AddNote(Note note) { notes.emplace_back(note); }
size_t Beatmap::NoteTime::size() const { return notes.size(); }
bool Beatmap::NoteTime::contains(Note note) {
    for (const auto& local_note : notes) {
        if (note == local_note)
            return true;
    }
    return false;
}

Beatmap::Beatmap(std::string beatmapFilename, Difficulty difficulty, std::string difficultyLabel)
    : beatmapFilename(std::move(beatmapFilename)), difficulty(difficulty),
      difficultyLabel(std::move(difficultyLabel)),
      arrow_sprite_sheet(SpriteSheet("../res/arrow-sprite.bmp", 3, 3)) {}

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

    std::cout << "Starting a beatmap: " << difficultyLabel << std::endl;

    std::ifstream ifs(beatmapFilename);
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
        //        std::cout << "Key pressed" << std::endl;
        Note pressedNote{};
        switch (event->key.keysym.sym) {
        case SDLK_F11:
            if (bFullScreen)
                SDL_SetWindowFullscreen(window, 0);
            else
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            break;
        case SDLK_UP:
            pressedNote = Note(Note::Type::TARGET, Note::Direction::UP);
            break;
        case SDLK_DOWN:
            pressedNote = Note(Note::Type::TARGET, Note::Direction::DOWN);
            break;
        case SDLK_LEFT:
            pressedNote = Note(Note::Type::TARGET, Note::Direction::LEFT);
            break;
        case SDLK_RIGHT:
            pressedNote = Note(Note::Type::TARGET, Note::Direction::RIGHT);
            break;
        }
        std::cout << (noteSet.front().contains(pressedNote) ? "Good!" : "Bad!") << std::endl;
    }
}

void Beatmap::OnLoop() {
    std::chrono::time_point<std::chrono::system_clock> tp2 = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedTime = tp2 - tp0;
    std::chrono::duration<float> delta = tp2 - tp1;

    const auto& front = noteSet.front();
    if (front.time > elapsedTime.count()) {
        //            std::cout << noteSet.front().time() -
        //            elapsedTime.count()
        //                      << std::endl;
    } else {
        std::cout << "New NoteTime containing " << front.size() << " notes" << std::endl;
        noteSet.pop();
        if (noteSet.empty())
            bRunning = false;
    }

    if (delta.count() >= 0.05) {
        tp1 = std::chrono::system_clock::now();
    }
}

void Beatmap::OnRender() {
    if (noteSet.empty())
        return;

    SDL_Surface* surf = SDL_GetWindowSurface(window);
    if (!surf) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        bRunning = false;
        return;
    }

    uint sprite_n;
    for (const auto& note : noteSet.front().notes) {
        switch (note.direction()) {
        case Note::Direction::UP:
            sprite_n = 4;
            break;
        case Note::Direction::DOWN:
            sprite_n = 5;
            break;
        case Note::Direction::LEFT:
            sprite_n = 6;
            break;
        case Note::Direction::RIGHT:
            sprite_n = 7;
            break;
        }

        arrow_sprite_sheet.Draw(surf, sprite_n, note.columnIndex() * surf->w / max_col_idx,
                                note.lineIndex() * surf->h / max_line_idx);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
