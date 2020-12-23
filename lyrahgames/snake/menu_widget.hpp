#pragma once
#include <ncurses.h>
//
#include <lyrahgames/snake/application.hpp>
#include <lyrahgames/snake/widget.hpp>

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

  void select_entry();

  void process_input(int input) override;
  void update() override;
  void render() override;
};

}  // namespace lyrahgames::snake