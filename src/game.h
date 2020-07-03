#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "grid.h"
#include "snake.h"
#include "renderer.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  //int GetScore() const;
  //int GetSize() const;
  bool CheckFoodPosition(int x, int y);
  void PrintResult(bool tie, Snake &winner);

 private:
  bool running{true};
  Grid grid_a;
  Grid grid_b;
  Snake snake_a;
  Snake snake_b;
  std::set<std::pair<int, int>> food_from_a_for_b;
  std::set<std::pair<int, int>> food_from_b_for_a;
  SDL_Point food;
  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  //int score{0};

  void PlaceFood();
  void Update();
  bool CheckFoddPosition();
  void PrintResultAccordingSize();
  void PrintResultAccordingDeath();
};

#endif