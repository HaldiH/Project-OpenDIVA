//
// Created by hugo on 5/7/20.
//

#ifndef OPENDIVA_SPRITE_HPP
#define OPENDIVA_SPRITE_HPP
#include <SDL2/SDL.h>
#include <string_view>
#include <vector>

class Sprite {
    friend class SpriteSheet;

  private:
    Sprite(int width, int height, SDL_PixelFormat* format);

  public:
    SDL_Surface* surface;
    explicit Sprite(std::string_view file);
    void Draw(SDL_Surface* dst, int x, int y);
};

class SpriteSheet {
  private:
    SDL_Surface* sprite_sheet;
    uint clip_width, clip_height;
    std::vector<SDL_Rect> clip_set;

  public:
    SpriteSheet(std::string_view file, uint n_rows, uint n_cols);
    void Draw(SDL_Surface* dst, uint sprite_n, int x, int y);
    [[nodiscard]] uint SpriteWidth() const;
    [[nodiscard]] uint SpriteHeight() const;
    [[nodiscard]] uint SpritesCount() const;
    Sprite GetSprite(uint sprite_n);
    std::vector<Sprite> GetSprites();
};

#endif // OPENDIVA_SPRITE_HPP
