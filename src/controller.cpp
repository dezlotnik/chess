#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::HandleInput(bool &running, int &mouse_x, int &mouse_y, bool &mouse_pressed, bool &mouse_lift) const { //std::vector<std::unique_ptr<Piece>> &black_pieces, std::vector<std::unique_ptr<Piece>> &white_pieces) const {
  SDL_Event e;
  SDL_GetMouseState(&mouse_x,&mouse_y);
  mouse_pressed = false;
  mouse_lift = false;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      switch (e.button.button) {
        case SDL_BUTTON_LEFT:
          mouse_pressed = true;
          break;
        default:
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      switch (e.button.button) {
        case SDL_BUTTON_LEFT:
          mouse_lift = true;
          break;
        default:
          break;
      }
    }
  }
}