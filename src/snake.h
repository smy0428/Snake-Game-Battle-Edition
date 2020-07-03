#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <set>
#include <utility>
#include <string>
#include "SDL.h"
#include "grid.h"


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight, kUpLeft, kUpRight, kDownLeft, kDownRight};


  Snake(int grid_width, int grid_height, int offset, std::string str)
      : grid_width(grid_width),
        grid_height(grid_height),
  		name(str),
        head_x(grid_width / 2 + offset),
        head_y(grid_height / 2),
  		pos_x(grid_width / 2 + offset),
        pos_y(grid_height / 2) {}

  void Update(Grid &grid);
  void GrowBody();
  bool SnakeCell(int x, int y);
  Direction direction = Direction::kUp;
  bool Win();

  std::string name;
  int pos_x;
  int pos_y;
  float speed{0.1f};
  float speedUp{0.02f};
  float minSpeed{0.1f};
  float maxSpeed{0.6f};
  void SpeedUp();
  void SlowDown();
  int size(){ return body.size(); };
  bool alive{true};
  bool noncrash{true};
  std::vector<SDL_Point> body;
  std::set<std::pair<int, int>> CutByPoint(int x, int y);



 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &prev_cell, Grid &grid);
  void UpdatePos(SDL_Point &prev_cell, SDL_Point &curr_cell, Grid &grid);
  bool growing{false};
  int grid_width;
  int grid_height;
  float head_x;
  float head_y;
  int winningSize{20};

};

#endif