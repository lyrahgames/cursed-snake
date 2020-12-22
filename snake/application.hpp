#pragma once
#include <chrono>
#include <thread>
//
#include <ncurses.h>
//
#include <snake/game.hpp>

namespace lyrahgames::snake {

class application {
 public:
  static constexpr int scale = 2;
  static constexpr float fps = 10;
  static constexpr float frame_time = 1 / fps;
  static constexpr float input_fps = 30;
  static constexpr float input_frame_time = 1 / input_fps;

  game state{};
  bool running = true;
  bool pause = true;
  WINDOW* window = nullptr;

  WINDOW* menu = nullptr;

  application() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);
    int cols, rows;
    getmaxyx(stdscr, rows, cols);
    window =
        newwin(state.height, scale * state.width, rows / 2 - state.height / 2,
               cols / 2 - scale * state.width / 2);

    int menu_width = 20;
    int menu_height = 10;
    menu = newwin(menu_height, menu_width, rows / 2 - menu_height / 2,
                  cols / 2 - menu_width / 2);
  }

  ~application() {
    delwin(window);
    endwin();
  }

  void process_input(int input) {
    switch (input) {
      case 'q':
        running = false;
        break;
      case 'p':
        pause = !pause;
        if (state.dead) state = game{};
        break;
      case KEY_UP:
        state.up();
        break;
      case KEY_DOWN:
        state.down();
        break;
      case KEY_RIGHT:
        state.right();
        break;
      case KEY_LEFT:
        state.left();
        break;
    }
  }

  void render() {
    mvprintw(0, 0, std::to_string(state.score).c_str());

    box(window, 0, 0);

    // move(state.food.y, scale * state.food.x);
    // addch(ACS_BULLET);
    mvwaddch(window, state.food.y, scale * state.food.x, ACS_DEGREE);

    for (auto [x, y] : state.snake) {
      // move(y, scale * x);
      // addch(ACS_DIAMOND);
      mvwaddch(window, y, scale * x, ACS_DIAMOND);
      // mvprintw(y, scale * x, "");
    }
  }

  void execute() {
    using namespace std;

    auto time = chrono::system_clock::now();
    auto input_time = time;

    refresh();

    while (running) {
      // Handle input events.
      int input;
      while ((input = getch()) != ERR) {
        process_input(input);
      }

      // Handle frame rate for rendering and advancing game state.
      auto new_time = chrono::system_clock::now();
      const auto time_diff = chrono::duration<float>(new_time - time).count();
      if (time_diff > frame_time) {
        time = new_time;

        if (pause) {
          wclear(menu);
          box(menu, 0, 0);
          mvwprintw(menu, 1, 1, "Pause");
          wrefresh(menu);
        } else {
          state.advance();
          if (state.dead) pause = true;
          wclear(window);
          render();
          wrefresh(window);
        }
        // clear();
        // refresh();
      }

      // Handel input frame rate.
      auto new_input_time = chrono::system_clock::now();
      const auto input_time_diff =
          chrono::duration<float>(new_input_time - input_time).count();
      this_thread::sleep_for(chrono::microseconds{
          static_cast<int>((input_frame_time - input_time_diff) * 1e6f)});
      input_time = new_input_time;
    }
  }

 private:
};

}  // namespace lyrahgames::snake