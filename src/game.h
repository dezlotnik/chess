#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <memory>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "piece.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  enum class Turn {
    None = 0,
    White = 1,
    Black = 2
  };

 private:
  std::size_t screen_width;
  std::size_t screen_height;
  std::vector<std::unique_ptr<Piece>> black_pieces_;
  std::vector<std::unique_ptr<Piece>> white_pieces_;
  void Update();
  void initializeFromFen(std::string fen, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces);
  void initializeGame(std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces);
  void handleMousePress();
  void handleMouseLift();
  int mouse_y_ = 0;
  int mouse_x_ = 0;
  bool mouse_pressed_ = false;
  bool mouse_lift_ = false;
  Turn turn_ = Turn::None;
};

#endif