#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <memory>
#include "piece.h"

class Controller {
 public:
  void HandleInput(bool &running, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const;
  void handleMousePress(int mouse_x, int mouse_y, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const;
  void handleMouseLift(int mouse_x, int mouse_y, std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const;

 private:
};

#endif