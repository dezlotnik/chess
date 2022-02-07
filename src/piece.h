#ifndef PIECE_H
#define PIECE_H

#include <string>

class Piece {
public:
  enum class Color {
      None = 0,
      White = 0,
      Black = 1
  };

  enum class Type {
      None = 0,
      Pawn = 1,
      Knight = 2,
      Bishop = 3,
      Rook = 4,
      Queen = 5,
      King = 6
  };
  Piece(Color color, Type type);


  std::string getImage() const {return image_;}
  size_t getHeight() const {return height_;}
  size_t getWidth() const {return width_;}

  int rank() const {return rank_;}
  int file() const {return file_;}
  void setRank(const int rank) {rank_ = rank;}
  void setFile(const int file) {file_ = file;}

  void setMoving(bool is_moving) {is_moving_ = is_moving;}
  bool isMoving() const {return is_moving_;}
  void setPosition(int x, int y) {x_ = x; y_ = y;}
  int x() const {return x_;};
  int y() const {return y_;};

private:
  Color color_;
  Type type_;
  std::string image_;

  void setImage(Color color, Type type);

  size_t height_ = 80;
  size_t width_;

  int file_ = 7;
  int rank_ = 7;

  bool is_moving_ = false;
  int x_;
  int y_;
};

#endif