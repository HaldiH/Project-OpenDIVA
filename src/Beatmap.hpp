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

class Note {
  public:
    enum class Type { TARGET, HOLD_TARGET, SLIDER, CHAIN_SLIDER };
    enum class Direction { UP, DOWN, LEFT, RIGHT };

  private:
    int _lineIndex, _columnIndex;
    Type _type;
    Direction _direction;

  public:
    Note() = default;
    explicit Note(Note::Type, Note::Direction);
    Note(int line_index, int column_index, Type, Direction);
    [[nodiscard]] Direction direction() const;
    [[nodiscard]] int lineIndex() const;
    [[nodiscard]] int columnIndex() const;
    [[nodiscard]] Type type() const;
    bool operator==(Note);
};

class Beatmap {
  public:
    enum class Difficulty { EASY, NORMAL, HARD, EXTREME, EXTRA_EXTREME };
    enum class Grades { WORST, WRONG, ALMOST, SAD, SAFE, FINE, COOL };

  private:
    bool bRunning = false, bFullScreen = false;
    std::string beatmapFilename, difficultyLabel;
    std::chrono::time_point<std::chrono::system_clock> tp0, tp1;
    Difficulty difficulty;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SpriteSheet arrow_sprite_sheet;
    const int max_line_idx = 3, max_col_idx = 3;
    struct NoteTime {
        std::vector<Note> notes;
        float time;

        NoteTime(Note note, float time);
        void AddNote(Note note);
        [[nodiscard]] size_t size() const;
        bool contains(Note);
    };
    std::queue<NoteTime> noteSet;

  public:
    Beatmap(std::string beatmapFilename, Difficulty difficulty, std::string difficultyLabel);
    bool OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event*);
    void OnLoop();
    void OnRender();
    void OnCleanup();
};

#endif // OPENDIVA_BEATMAP_HPP
