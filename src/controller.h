#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
 public:
  void HandleInput(bool &running, int &mouse_x, int &mouse_y, bool &mouse_pressed, bool &mouse_lift) const;
 private:
};

#endif