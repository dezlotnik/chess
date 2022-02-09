#include "piece.h"

Piece::Piece(Color color, Type type) : color_(color), type_(type) {
  setImage(color, type);
}

bool Piece::blocked(const Move &move, const std::vector<std::unique_ptr<Piece>>& pieces) const {
  for (auto &piece : pieces) {
    if (move.rank == piece->rank() && move.file == piece->file()) {
      return true;
    }
  }
  return false;
}

std::vector<Piece::Move> Piece::legalMoves(const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces) const {
  std::vector<Move> moves;

  auto &pieces = (color_ == Color::White) ? white_pieces : black_pieces;
  auto &enemy_pieces = (color_ == Color::White) ? black_pieces : white_pieces;

  if (type_ == Type::Queen || type_ == Type::Rook) {
    std::vector<std::vector<int>> move_directions = { {-1,0}, {0,-1}, {1, 0}, {0, 1} };
    for (auto d : move_directions) {
      for (int i = 0; i < 8; i++) {
        Move move;
        move.rank = rank_ + i*d[0];
        move.file = file_ + i*d[1];
        if (blocked(move, pieces)) {
          break;
        }
        if (blocked(move, enemy_pieces)) {
          moves.push_back(move);
          break;
        }
        if (move.rank < 8 && move.rank >= 0 && move.file < 8 && move.file >= 0) {
          moves.push_back(move);
        }
      }
    }
  }

  if (type_ == Type::Queen || type_ == Type::Bishop) {
    std::vector<std::vector<int>> move_directions = { {-1,-1}, {-1,1}, {1, -1}, {1, 1} };
    for (auto d : move_directions) {
      for (int i = 0; i < 8; i++) {
        Move move;
        move.rank = rank_ + i*d[0];
        move.file = file_ + i*d[1];
        if (blocked(move, pieces)) {
          break;
        }
        if (blocked(move, enemy_pieces)) {
          moves.push_back(move);
          break;
        }
        if (move.rank < 8 && move.rank >= 0 && move.file < 8 && move.file >= 0) {
          moves.push_back(move);
        }
      }
    }
  }
  
  if (type_ == Type::Pawn) {
    std::vector<int> move_direction = {1,0};
    std::vector<std::vector<int>> attack_directions = { {1,1}, {1,-1} };
    int up_dir = (color_ == Color::White) ? -1 : 1;
    int starting_rank = (color_ == Color::White) ? 6 : 1;
    Move move;
    move.rank = rank_ + up_dir*move_direction[0];
    move.file = file_ + up_dir*move_direction[1];
    if (!blocked(move, pieces) && !blocked(move, enemy_pieces)) {
      moves.push_back(move);
    }
    if (rank_ == starting_rank) {
      Move move;
      move.rank = rank_ + 2*up_dir*move_direction[0];
      move.file = file_ + 2*up_dir*move_direction[1];
      if (!blocked(move, pieces) && !blocked(move, enemy_pieces)) {
        moves.push_back(move);
      }
    }
    for (auto d : attack_directions) {
      Move move;
      move.rank = rank_ + up_dir*d[0];
      move.file = file_ + up_dir*d[1];
      if (blocked(move, enemy_pieces)) {
        moves.push_back(move);
      }
    }
  }

  if (type_ == Type::King) {
    std::vector<int> ranks = {-1, 0, 1};
    std::vector<int> files = {-1, 0, 1};
    for (int r : ranks) {
      for (int f : files) {
        Move move;
        move.rank = rank_ + r;
        move.file = file_ + f;
        if (move.rank < 8 && move.rank >= 0 && move.file < 8 && move.file >= 0 && !blocked(move, pieces)) {
          moves.push_back(move);
        }
      }
    }
  }

  if (type_ == Type::Knight) {
    std::vector<std::vector<int>> diags = { {-2,-1}, {-1,-2}, {2,-1}, {1, -2}, {-2, 1}, {-1, 2}, {2, 1}, {1, 2} };
    for (auto d : diags) {
      Move move;
      move.rank = rank_ + d[0];
      move.file = file_ + d[1];
      if (move.rank < 8 && move.rank >= 0 && move.file < 8 && move.file >= 0 && !blocked(move, pieces)) {
        moves.push_back(move);
      }
    }
  }

  return moves;
}

void Piece::setImage(Color color, Type type) {
  if (color == Color::White) {
    switch (type) {
      case Type::Pawn:
        image_ = "../assets/w_pawn_png_80px.png";
        width_ = 66;
        break;
      case Type::Knight:
        image_ = "../assets/w_knight_png_80px.png";
        width_ = 72;
        break;
      case Type::Bishop:
        image_ = "../assets/w_bishop_png_80px.png";
        width_ = 79;
        break;
      case Type::Rook:
        image_ = "../assets/w_rook_png_80px.png";
        width_ = 73;
        break;
      case Type::Queen:
        image_ = "../assets/w_queen_png_80px.png";
        width_ = 88;
        break;
      case Type::King:
        image_ = "../assets/w_king_png_80px.png";
        width_ = 79;
        break;
    }
  }

  if (color == Color::Black) {
    switch (type) {
      case Type::Pawn:
        image_ = "../assets/b_pawn_png_80px.png";
        width_ = 66;
        break;
      case Type::Knight:
        image_ = "../assets/b_knight_png_80px.png";
        width_ = 72;
        break;
      case Type::Bishop:
        image_ = "../assets/b_bishop_png_80px.png";
        width_ = 79;
        break;
      case Type::Rook:
        image_ = "../assets/b_rook_png_80px.png";
        width_ = 73;
        break;
      case Type::Queen:
        image_ = "../assets/b_queen_png_80px.png";
        width_ = 88;
        break;
      case Type::King:
        image_ = "../assets/b_king_png_80px.png";
        width_ = 79;
        break;
    }
  }
}