#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <set>
#include <utility>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const &snake_a, Snake const &snake_b, SDL_Point const &food, std::set<std::pair<int, int>> &food_from_a_for_b, std::set<std::pair<int, int>> &food_from_b_for_a);
  void UpdateWindowTitle(int score_a, int score_b, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif