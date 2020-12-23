#include <snake/game_widget.hpp>
#include <snake/menu_widget.hpp>

namespace lyrahgames::snake {

game_widget::game_widget() {
  int cols, rows;
  getmaxyx(stdscr, rows, cols);
  window = newwin(game.height, scale * game.width, rows / 2 - game.height / 2,
                  cols / 2 - scale * game.width / 2);
}
game_widget::~game_widget() {
  if (window) delwin(window);
}

void game_widget::process_input(int input) {
  switch (input) {
    case ' ':
      pause();
      break;
    case KEY_UP:
      game.up();
      break;
    case KEY_DOWN:
      game.down();
      break;
    case KEY_RIGHT:
      game.right();
      break;
    case KEY_LEFT:
      game.left();
      break;
  }
}

void game_widget::pause() {
  is_paused = true;
  menu->visible = true;
  app.focus = menu;
}

void game_widget::play() {
  is_paused = false;
  menu->visible = false;
  app.focus = this;
}

void game_widget::update() {
  if (is_paused) return;
  if (game.dead) game = {};

  using namespace std;
  // Handle frame rate for rendering and advancing game state.
  auto new_time = chrono::system_clock::now();
  const auto time_diff = chrono::duration<float>(new_time - time).count();
  if (time_diff > transition_time) {
    time = new_time;

    game.advance();
    if (game.dead) pause();
  }
}

void game_widget::render() {
  wclear(window);

  // Draw food.
  mvwaddch(window, game.food.y, scale * game.food.x, ACS_DEGREE);
  // Draw snake.
  for (auto [x, y] : game.snake) mvwaddch(window, y, scale * x, ACS_DIAMOND);
  // Draw walls.
  box(window, 0, 0);

  wrefresh(window);
}

}  // namespace lyrahgames::snake