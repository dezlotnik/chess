#include <memory>
#include <sstream>
#include "SDL.h"
#include "game.h"
#include <iostream>


Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::cout << "Initializing game...";
  initializeGame(black_pieces_, white_pieces_);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, black_pieces_, white_pieces_);
    Update();
    renderer.Render(black_pieces_, white_pieces_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {}

void Game::initializeFromFen(std::string fen, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) {
 // todo
}

void Game::initializeGame(std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) {
  std::unique_ptr<Piece> black_rook = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Rook);
  black_rook->setRank(0);
  black_rook->setFile(0);
  black_pieces.push_back(std::move(black_rook));

  std::unique_ptr<Piece> black_knight = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Knight);
  black_knight->setRank(0);
  black_knight->setFile(1);
  black_pieces.push_back(std::move(black_knight));

  std::unique_ptr<Piece> black_bishop = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Bishop);
  black_bishop->setRank(0);
  black_bishop->setFile(2);
  black_pieces.push_back(std::move(black_bishop));

  std::unique_ptr<Piece> black_queen = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Queen);
  black_queen->setRank(0);
  black_queen->setFile(3);
  black_pieces.push_back(std::move(black_queen));

  std::unique_ptr<Piece> black_king = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::King);
  black_king->setRank(0);
  black_king->setFile(4);
  black_pieces.push_back(std::move(black_king));

  std::unique_ptr<Piece> black_rook2 = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Rook);
  black_rook2->setRank(0);
  black_rook2->setFile(7);
  black_pieces.push_back(std::move(black_rook2));

  std::unique_ptr<Piece> black_knight2 = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Knight);
  black_knight2->setRank(0);
  black_knight2->setFile(6);
  black_pieces.push_back(std::move(black_knight2));

  std::unique_ptr<Piece> black_bishop2 = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Bishop);
  black_bishop2->setRank(0);
  black_bishop2->setFile(5);
  black_pieces.push_back(std::move(black_bishop2));

  for (size_t file = 0; file < 8; file++) {
    std::unique_ptr<Piece> black_pawn = std::make_unique<Piece>(Piece::Color::Black, Piece::Type::Pawn);
    black_pawn->setRank(1);
    black_pawn->setFile(file);
    black_pieces.push_back(std::move(black_pawn));
  }

  // White pieces
  std::unique_ptr<Piece> white_rook = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Rook);
  white_rook->setRank(7);
  white_rook->setFile(0);
  white_pieces.push_back(std::move(white_rook));

  std::unique_ptr<Piece> white_knight = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Knight);
  white_knight->setRank(7);
  white_knight->setFile(1);
  white_pieces.push_back(std::move(white_knight));

  std::unique_ptr<Piece> white_bishop = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Bishop);
  white_bishop->setRank(7);
  white_bishop->setFile(2);
  white_pieces.push_back(std::move(white_bishop));

  std::unique_ptr<Piece> white_queen = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Queen);
  white_queen->setRank(7);
  white_queen->setFile(3);
  white_pieces.push_back(std::move(white_queen));

  std::unique_ptr<Piece> white_king = std::make_unique<Piece>(Piece::Color::White, Piece::Type::King);
  white_king->setRank(7);
  white_king->setFile(4);
  white_pieces.push_back(std::move(white_king));

  std::unique_ptr<Piece> white_rook2 = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Rook);
  white_rook2->setRank(7);
  white_rook2->setFile(7);
  white_pieces.push_back(std::move(white_rook2));

  std::unique_ptr<Piece> white_knight2 = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Knight);
  white_knight2->setRank(7);
  white_knight2->setFile(6);
  white_pieces.push_back(std::move(white_knight2));

  std::unique_ptr<Piece> white_bishop2 = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Bishop);
  white_bishop2->setRank(7);
  white_bishop2->setFile(5);
  white_pieces.push_back(std::move(white_bishop2));

  for (size_t file = 0; file < 8; file++) {
    std::unique_ptr<Piece> white_pawn = std::make_unique<Piece>(Piece::Color::White, Piece::Type::Pawn);
    white_pawn->setRank(6);
    white_pawn->setFile(file);
    white_pieces.push_back(std::move(white_pawn));
  }
}