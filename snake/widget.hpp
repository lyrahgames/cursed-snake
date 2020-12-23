#pragma once

namespace lyrahgames::snake {

class widget {
 public:
  widget() = default;
  virtual ~widget() = default;

  virtual void process_input(int input) = 0;
  virtual void update(){};
  virtual void render() = 0;
};

}  // namespace lyrahgames::snake