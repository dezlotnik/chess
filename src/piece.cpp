#include "piece.h"

Piece::Piece(Color color, Type type) : color_(color), type_(type) {
  setImage(color, type);
}

std::vector<Piece::Move> Piece::legalMoves(const std::vector<std::unique_ptr<Piece>>& black_pieces, const std::vector<std::unique_ptr<Piece>>& white_pieces) const {
  std::vector<Move> moves;

  auto &pieces = (color_ == Color::White) ? white_pieces : black_pieces;
  
  for (int rank = rank_; rank < 8; rank++) {
    bool end_search = false;
    Move move;
    move.rank = rank;
    move.file = file_;
    for (auto &piece : pieces) {
      if (piece->rank() == move.rank && piece->file() == move.file) {
        end_search = true;
        break;
      }
    }
    if (end_search) {
      break;
    }
    moves.push_back(move);
  }

  for (int rank = rank_; rank >= 0; rank--) {
    bool end_search = false;
    Move move;
    move.rank = rank;
    move.file = file_;
    for (auto &piece : pieces) {
      if (piece->rank() == move.rank && piece->file() == move.file) {
        end_search = true;
        break;
      }
    }
    if (end_search) {
      break;
    }
    moves.push_back(move);
  }

  for (int file = file_; file < 8; file++) {
    bool end_search = false;
    Move move;
    move.rank = rank_;
    move.file = file;
    for (auto &piece : pieces) {
      if (piece->rank() == move.rank && piece->file() == move.file) {
        end_search = true;
        break;
      }
    }
    if (end_search) {
      break;
    }
    moves.push_back(move);
  }

  for (int file = file_; file >= 0; file--) {
    bool end_search = false;
    Move move;
    move.rank = rank_;
    move.file = file;
    for (auto &piece : pieces) {
      if (piece->rank() == move.rank && piece->file() == move.file) {
        end_search = true;
        break;
      }
    }
    if (end_search) {
      break;
    }
    moves.push_back(move);
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