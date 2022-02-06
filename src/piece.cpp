#include "piece.h"

Piece::Piece(Color color, Type type) : color_(color), type_(type) {
  setImage(color, type);
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