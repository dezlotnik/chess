#include "renderer.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "piece.h"

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

void Renderer::Render(const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces, const std::unique_ptr<Piece> &selected_piece) {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect r;
  r.x = 0;
  r.y = 0;
  r.w = square_size;
  r.h = square_size;

  // Render board
  for (int rank = 0; rank < 8; rank++) {
    Color square_color;
    for (int file = 0; file < 8; file++) {
      square_color = (file+rank)%2 == 0 ? light_color_ : dark_color_;
      SDL_SetRenderDrawColor(sdl_renderer, square_color.r, square_color.g, square_color.b, square_color.alpha);
      SDL_RenderFillRect(sdl_renderer, &r);
      r.x += square_size;
    }
    r.x = 0;
    r.y += square_size;
  }

  // Render pieces
  for (const std::unique_ptr<Piece> &piece: black_pieces) {
    RenderStaticPiece(piece.get());
  }

  for (const std::unique_ptr<Piece> &piece: white_pieces) {
    RenderStaticPiece(piece.get());
  }

  if (selected_piece) {
    RenderSelectedPiece(selected_piece.get(), black_pieces, white_pieces);
  }
  

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int fps) {
  std::string title{"Chess! FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderStaticPiece(const Piece *piece,  bool render_bounding_box) {
  SDL_Surface *surface = IMG_Load((piece->getImage()).c_str());
  if (nullptr == surface) {
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);
  SDL_Rect destination;
  destination.x = piece->file()*square_size + (square_size - piece->getWidth())/2;
  destination.y = piece->rank()*square_size + (square_size - piece->getHeight())/2;
  destination.w = piece->getWidth();
  destination.h = piece->getHeight();
  SDL_RenderCopy(sdl_renderer, texture, NULL, &destination);
  SDL_DestroyTexture(texture);

  if (render_bounding_box) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &destination);
  }
}

void Renderer::RenderSelectedPiece(const Piece *piece, const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces,  bool render_bounding_box) {
  SDL_Surface *surface = IMG_Load((piece->getImage()).c_str());
  if (nullptr == surface) {
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);
  SDL_Rect destination;
  destination.x = piece->x() - piece->getWidth()/2;
  destination.y = piece->y() - piece->getHeight()/2;
  destination.w = piece->getWidth();
  destination.h = piece->getHeight();
  SDL_RenderCopy(sdl_renderer, texture, NULL, &destination);
  SDL_DestroyTexture(texture);

  if (render_bounding_box) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    SDL_RenderDrawRect(sdl_renderer, &destination);
  }

  for (auto move : piece->legalMoves(black_pieces, white_pieces)) {
    SDL_Rect r;
    r.x = square_size*move.file;
    r.y = square_size*move.rank;
    r.w = square_size;
    r.h = square_size;
    SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(sdl_renderer, 72, 191, 173, 50);
    SDL_RenderFillRect(sdl_renderer, &r);
  }
}