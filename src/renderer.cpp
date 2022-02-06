#include "renderer.h"
#include <iostream>
#include <string>
#include "SDL_image.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      square_size(screen_height/8) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("CHESS!", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render() {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect r;
  r.x = 0;
  r.y = 0;
  r.w = square_size;
  r.h = square_size;

  // Render rect
  Color *first_color = &light_color_;
  Color *second_color = &dark_color_;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (j%2 == 0) {
        SDL_SetRenderDrawColor(sdl_renderer, first_color->r, first_color->g, first_color->b, first_color->alpha);
      } else {
        SDL_SetRenderDrawColor(sdl_renderer, second_color->r, second_color->g, second_color->b, second_color->alpha);
      }
      SDL_RenderFillRect(sdl_renderer, &r);
      r.x += square_size;
    }
    r.x = 0;
    r.y += square_size;
    Color *tmp;
    tmp = first_color;
    first_color = second_color;
    second_color = tmp;
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
  std::string title{"Chess! FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}