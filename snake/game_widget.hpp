#pragma once
#include <chrono>
//
#include <ncurses.h>
//
#include <snake/game_state.hpp>
#include <snake/widget.hpp>

namespace lyrahgames::snake {

class menu_widget;

class game_widget : public widget {
 public:
  static constexpr int scale = 2;
  bool is_paused = true;
  game_state game{};
  menu_widget* menu = nullptr;
  WINDOW* window = nullptr;
  float transition_time = 1.0f / 3.0f;

  std::chrono::time_point<std::chrono::system_clock> time =
      std::chrono::system_clock::now();

  game_widget();
  ~game_widget();

  void pause();
  void play();

  void process_input(int input) override;
  void update() override;
  void render() override;
};

}  // namespace lyrahgames::snake