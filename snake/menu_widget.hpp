#pragma once
#include <ncurses.h>
//
#include <snake/application.hpp>
#include <snake/widget.hpp>

namespace lyrahgames::snake {

class game_widget;

class menu_widget : public widget {
 public:
  int select = 0;
  WINDOW* window = nullptr;
  int width = 20;
  int height = 10;
  bool visible = true;
  game_widget* game;

  menu_widget();
  ~menu_widget();

  void process_input(int input) override;
  void update();
  void render();
};

}  // namespace lyrahgames::snake