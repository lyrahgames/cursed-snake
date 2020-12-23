#include <lyrahgames/snake/game_widget.hpp>
#include <lyrahgames/snake/menu_widget.hpp>

namespace lyrahgames::snake {

menu_widget::menu_widget() {
  int cols, rows;
  getmaxyx(stdscr, rows, cols);
  window = newwin(height, width, rows / 2 - height / 2, cols / 2 - width / 2);
}
menu_widget::~menu_widget() {
  if (window) delwin(window);
}

void menu_widget::process_input(int input) {
  switch (input) {
    case 'q':
      app.quit();
      break;
    case ' ':
      game->play();
      break;
    case KEY_UP:
      break;
    case KEY_DOWN:
      break;
  }
}

void menu_widget::update() {}

void menu_widget::render() {
  if (!visible) return;

  wclear(window);
  box(window, 0, 0);
  mvwprintw(window, 1, 1, "Pause");
  wrefresh(window);
}

}  // namespace lyrahgames::snake