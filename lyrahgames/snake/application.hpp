#pragma once
#include <chrono>
#include <list>
#include <thread>
//
#include <ncurses.h>
//
#include <lyrahgames/snake/widget.hpp>

namespace lyrahgames::snake {

class application {
 public:
  static constexpr float fps = 10;
  static constexpr float frame_time = 1 / fps;

  bool running = true;
  std::list<widget*> widgets{};
  widget* focus = nullptr;

 public:
  application();
  ~application();

  void init_ui();

  void execute();
  void add_widget(widget* w);
  void quit() { running = false; }

 private:
};

extern application app;

}  // namespace lyrahgames::snake