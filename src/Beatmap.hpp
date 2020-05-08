//
// Created by hugo on 4/24/20.
//

#ifndef OPENDIVA_BEATMAP_HPP
#define OPENDIVA_BEATMAP_HPP

#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <chrono>
#include <queue>
#include <string>

enum class Difficulty { EASY, NORMAL, HARD, EXTREME, EXTRA_EXTREME };

enum class Grades { WORST, WRONG, ALMOST, SAD, SAFE, FINE, COOL };

class Note {
  public:
    enum Type { TARGET, HOLD_TARGET, SLIDER, CHAIN_SLIDER };
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Note(int line_index, int column_index, Type, Direction);
    [[nodiscard]] Direction direction() const;
    [[nodiscard]] int lineIndex() const;
    [[nodiscard]] int columnIndex() const;
    [[nodiscard]] Type type() const;

  private:
    int _lineIndex;
    int _columnIndex;
    Type _type;
    Direction _direction;
};

struct NoteTime {
    uint8_t size;
    std::vector<Note> notes;
    float time;

    NoteTime(Note note, float time);
    void AddNote(Note note);
};

struct BeatmapParams {
    std::string _beatmapFilename;
    std::string _difficultyLabel;
    Difficulty _difficulty;

    BeatmapParams(std::string beatmapFilename, std::string difficultyLabel, Difficulty);
};

class Beatmap {
  private:
    bool bRunning = false, bFullScreen = false;
    std::chrono::time_point<std::chrono::system_clock> tp0, tp1;
    std::queue<NoteTime> noteSet;
    BeatmapParams params;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SpriteSheet spriteSheet;

  public:
    explicit Beatmap(BeatmapParams);
    bool OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event*);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif // OPENDIVA_BEATMAP_HPP
