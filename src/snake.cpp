#include "snake.h"
#include <cmath>
#include <iostream>
#include <algorithm>

void Snake::Update(Grid &grid) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point curr_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  /*
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
  */
  UpdatePos(prev_cell, curr_cell, grid);
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
    
    case Direction::kUpLeft:
      head_x -= sqrt(2) / 2 * speed;
      head_y -= sqrt(2) / 2 * speed;
      break;
     
    case Direction::kDownRight:
      head_x += sqrt(2) / 2 * speed;
      head_y += sqrt(2) / 2 * speed;
      break;
      
    case Direction::kUpRight:
      head_x += sqrt(2) / 2 * speed;
      head_y -= sqrt(2) / 2 * speed;
      break;

    case Direction::kDownLeft:
      head_x -= sqrt(2) / 2 * speed;
      head_y += sqrt(2) / 2 * speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &prev_head_cell, Grid &grid) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  grid.SetBody(prev_head_cell.x, prev_head_cell.y);

  if (!growing) {
    // Remove the tail from the vector.
    SDL_Point tail = body.front();
    grid.Clear(tail.x, tail.y);
    body.erase(body.begin());
  } else {
    growing = false;
  }

  // Check if the snake has died. The head will be updated in the Game.cpp
  if (grid.CrashBody(pos_x, pos_y)) { 
      alive = false; 
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == pos_x && y == pos_y) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::UpdatePos(SDL_Point &prev_cell, SDL_Point &curr_cell, Grid &grid) {
  	// entering a new grid
  	if (prev_cell.x != curr_cell.x || prev_cell.y != curr_cell.y) {
      	// easy case with normal directions
      	if (direction == Direction::kUp || direction == Direction::kDown || direction ==  Direction::kLeft || direction ==  Direction::kRight) {
          	pos_x = curr_cell.x;
         	pos_y = curr_cell.y;
          	UpdateBody(prev_cell, grid);
         	return;
        }
      	// diagonal directions, x&y must both be changed
      	if (curr_cell.x != pos_x && curr_cell.y != pos_y) {
          	prev_cell.x = pos_x;
          	prev_cell.y = pos_y;
        	pos_x = curr_cell.x;
         	pos_y = curr_cell.y;
          	UpdateBody(prev_cell, grid);
         	return;
        }
    }
}


std::set<std::pair<int, int>> Snake::CutByPoint(int x, int y) {
  	// std::cout << "snake crahsed one time at (x, y)!" << "\n";
  	std::set<std::pair<int, int>> tails;
  	SDL_Point curr = body.front();
 	tails.insert(std::pair(curr.x, curr.y));
	while (curr.x != x && curr.y != y) {
      	SlowDown();
    	body.erase(body.begin());
		curr = body.front();
      	tails.insert(std::pair(curr.x, curr.y));
    }
  	return tails;
}
  
bool Snake::Win() { return size() >= winningSize; }
void Snake::SpeedUp() { speed = std::min(speed + speedUp, maxSpeed); }
void Snake::SlowDown() { speed = std::max(speed - speedUp, minSpeed); }