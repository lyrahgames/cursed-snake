#pragma once
#include <list>
#include <random>

namespace lyrahgames::snake {

struct position {
  int x{};
  int y{};
};

struct game_state {
  bool dead = false;

  size_t width{32};
  size_t height{16};

  std::list<position> snake{{10, 10}, {10, 11}, {11, 11}};
  position direction{0, -1};
  position food{};
  size_t score{};

  std::mt19937 rng{std::random_device{}()};

  game_state() { spawn_food(); }

  void spawn_food() {
    std::uniform_int_distribution<int> distribution_x(1, width - 2);
    std::uniform_int_distribution<int> distribution_y(1, height - 2);

    bool gen;
    do {
      gen = false;
      food = {distribution_x(rng), distribution_y(rng)};
      for (auto p : snake) {
        if ((p.x == food.x) && (p.y == food.y)) {
          gen = true;
          break;
        }
      }
    } while (gen);
  }

  void advance() {
    position head{snake.front().x + direction.x, snake.front().y + direction.y};

    bool gen = false;
    if ((head.x == food.x) && (head.y == food.y)) {
      gen = true;
    } else {
      snake.pop_back();
    }
    for (auto p : snake) {
      if ((p.x == head.x) && (p.y == head.y)) {
        dead = true;
        break;
      }
    }
    snake.push_front(head);

    if (gen) {
      ++score;
      spawn_food();
    }

    if ((head.x >= width - 1) || (head.x == 0) || (head.y >= height - 1) ||
        (head.y == 0))
      dead = true;
  }

  bool is_valid_direction(position d) {
    auto it = begin(snake);
    auto head = *it;
    ++it;
    auto body = *it;
    if (((head.x + d.x) == body.x) && ((head.y + d.y) == body.y)) return false;
    return true;
  }

  void up() {
    position tmp{0, -1};
    if (is_valid_direction(tmp)) direction = tmp;
  }

  void down() {
    position tmp{0, 1};
    if (is_valid_direction(tmp)) direction = tmp;
  }

  void right() {
    position tmp{1, 0};
    if (is_valid_direction(tmp)) direction = tmp;
  }

  void left() {
    position tmp{-1, 0};
    if (is_valid_direction(tmp)) direction = tmp;
  }
};

}  // namespace lyrahgames::snake