#pragma once

namespace lyrahgames::snake {

struct menu {
  int select = 0;
  WINDOW *window = nullptr;
  int width = 10;
  int height = 10;

  menu() {
    window = newwin(height, width, rows / 2 - height / 2, cols / 2 - width / 2);
  }
  ~menu() { delwin(window); }

  void process_input() {
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
    wclear(window);
    box(window, 0, 0);
    mvwprintw(window, 1, 1, "Pause");
    wrefresh(window);
  }
};

}  // namespace lyrahgames::snake