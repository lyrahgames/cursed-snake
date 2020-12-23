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
    case ' ':
      game->play();
      break;
    case KEY_UP:
      select = (select + 2) % 3;
      break;
    case KEY_DOWN:
      select = (select + 1) % 3;
      break;
    case '\n':
      select_entry();
      break;
  }
}

void menu_widget::select_entry() {
  switch (select) {
    case 0:
      game->play();
      break;
    case 1:
      game->restart();
      break;
    case 2:
      app.quit();
      break;
  }

  select = 0;
}

void menu_widget::update() {}

void menu_widget::render() {
  if (!visible) return;

  wclear(window);

  box(window, 0, 0);

  mvwprintw(window, 1, 4, "Cursed Snake");
  mvwaddch(window, 2, 8, ACS_DIAMOND);
  mvwaddch(window, 2, 9, ACS_DIAMOND);
  mvwaddch(window, 2, 10, ACS_DIAMOND);
  mvwaddch(window, 2, 11, ACS_DIAMOND);
  // wattroff(window, A_STANDOUT);

  if (select == 0) wattron(window, A_STANDOUT);
  mvwprintw(window, 4, 1, "     Continue     ");
  if (select == 0) wattroff(window, A_STANDOUT);

  if (select == 1) wattron(window, A_STANDOUT);
  mvwprintw(window, 6, 1, "     New Game     ");
  if (select == 1) wattroff(window, A_STANDOUT);

  if (select == 2) wattron(window, A_STANDOUT);
  mvwprintw(window, 8, 1, "       Exit       ");
  if (select == 2) wattroff(window, A_STANDOUT);

  wrefresh(window);
}

}  // namespace lyrahgames::snake