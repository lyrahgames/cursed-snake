#include <lyrahgames/snake/application.hpp>
#include <lyrahgames/snake/game_widget.hpp>
#include <lyrahgames/snake/menu_widget.hpp>

namespace lyrahgames::snake {

application::application() {
  // Initialize ncurses library state.
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  curs_set(0);

  init_ui();
}

application::~application() {
  // Delete widgets.
  for (auto w : widgets) delete w;

  // Free ncurses library state.
  endwin();
}

void application::init_ui() {
  auto game = new game_widget{};
  auto menu = new menu_widget{};
  menu->game = game;
  game->menu = menu;
  add_widget(game);
  add_widget(menu);
}

void application::add_widget(widget* w) {
  if (!w) return;
  widgets.push_back(w);
  focus = w;
}

void application::execute() {
  using namespace std;

  auto time = chrono::system_clock::now();

  // Start the game loop.
  while (running) {
    // Handle input events.
    int input;
    while ((input = getch()) != ERR) {
      if (focus) focus->process_input(input);
    }

    // Update all widgets.
    for (auto w : widgets) w->update();
    // Render all widgets.
    for (auto w : widgets) w->render();

    // Handel frame rate.
    auto new_time = chrono::system_clock::now();
    const auto input_time_diff =
        chrono::duration<float>(new_time - time).count();
    this_thread::sleep_for(chrono::microseconds{
        static_cast<int>((frame_time - input_time_diff) * 1e6f)});
    time = new_time;
  }
}

application app{};

}  // namespace lyrahgames::snake