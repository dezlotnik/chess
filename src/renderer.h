#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "piece.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces, const std::unique_ptr<Piece>& selected_piece);
  void UpdateWindowTitle(int fps);
  void RenderStaticPiece(const Piece *piece, bool render_bounding_box = false);
  void RenderSelectedPiece(const Piece *piece, const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces, bool render_bounding_box = false);

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

  const Color light_color_ = {238, 238, 210, 255};
  const Color dark_color_ = {118, 150, 86, 255};
};

#endif