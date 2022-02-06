#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render();
  void UpdateWindowTitle(int fps);

  struct Color {
    size_t r = 0;
    size_t g = 0;
    size_t b = 0;
    size_t alpha = 255;
  };

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t square_size;

  const Color light_color_ = {170, 170, 170, 255};
  const Color dark_color_ = {68, 68, 68, 255};
};

#endif