#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const {
  SDL_Event e;
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x,&mouse_y);
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      switch (e.button.button) {
        case SDL_BUTTON_LEFT:
          handleMousePress(mouse_x, mouse_y, black_pieces, white_pieces);
          break;
        default:
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      switch (e.button.button) {
        case SDL_BUTTON_LEFT:
          handleMouseLift(mouse_x, mouse_y, black_pieces, white_pieces);
          break;
        default:
          break;
      }
    }
  }
  
  for (auto &piece : black_pieces) {
    if (piece->isMoving()) {
      piece->setPosition(mouse_x, mouse_y);
    }
  }

  for (auto &piece : white_pieces) {
    if (piece->isMoving()) {
      piece->setPosition(mouse_x, mouse_y);
    }
  }


}

void Controller::handleMousePress(int mouse_x, int mouse_y, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const {
  // find which square the mouse press was in...
  int rank;
  int file;
  rank = mouse_y/100;
  file = mouse_x/100;

  for (auto &piece : black_pieces) {
    if (piece->rank() == rank && piece->file() == file) {
      piece->setMoving(true);
    }
  }

  for (auto &piece : white_pieces) {
    if (piece->rank() == rank && piece->file() == file) {
      piece->setMoving(true);
    }
  }
}

void Controller::handleMouseLift(int mouse_x, int mouse_y, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const {
  // find which square the mouse press was in...
  int rank;
  int file;
  rank = mouse_y/100;
  file = mouse_x/100;

  for (auto &piece : black_pieces) {
    if (piece->isMoving()) {
      piece->setMoving(false);
      piece->setRank(rank);
      piece->setFile(file);
    }
  }

  for (auto &piece : white_pieces) {
    if (piece->isMoving()) {
      piece->setMoving(false);
      piece->setRank(rank);
      piece->setFile(file);
    }
  }
}