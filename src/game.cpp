#include "game.h"
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include <thread>


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_a(grid_width, grid_height, -4, "Player One Blue"),
	  snake_b(grid_width, grid_height, 4, "Player Two Red"),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
	  grid_a(grid_width, grid_height),
	  grid_b(grid_width, grid_height)
{
        
       //grid_a(grid_width, grid_height);
        //grid_b(grid_width, grid_height);
        grid_a.SetHead(snake_a.pos_x, snake_a.pos_y);
        grid_b.SetHead(snake_b.pos_x, snake_b.pos_y);
        PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  while (running) {
    frame_start = SDL_GetTicks();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake_a, snake_b);
    Update();
    renderer.Render(snake_a, snake_b, food, food_from_a_for_b, food_from_b_for_a);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(snake_a.size(), snake_b.size(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (CheckFoodPosition(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake_a.alive && !snake_b.alive) { 
      PrintResultAccordingSize(); 
      snake_a.alive = false;
      snake_b.alive = false;
      running = false;
      return; 
  }
  if (!snake_a.alive || !snake_b.alive) { 
      PrintResultAccordingDeath(); 
      snake_a.alive = false;
      snake_b.alive = false;
      running = false;
      return; 
  }  
  if (snake_a.Win() || snake_b.Win()) { 
      PrintResultAccordingSize();
      snake_a.alive = false;
      snake_b.alive = false;
      running = false;
      return; 
  }

  snake_a.Update(grid_a);
  snake_b.Update(grid_b);
  
  // They kill each other
  
  if (snake_a.pos_x == snake_b.pos_x && snake_a.pos_y == snake_b.pos_y) { 
      PrintResultAccordingSize();
      snake_a.alive = false;
      snake_b.alive = false;
      running = false;
      return;  }
      

  // Check snake_a safety
  if (grid_a.CrashBody(snake_b.pos_x, snake_b.pos_y)) {
      std::set<std::pair<int, int>> temp = snake_a.CutByPoint(snake_b.pos_x, snake_b.pos_y);
      food_from_a_for_b.insert(temp.begin(), temp.end());
  	  //food_from_a_for_b = snake_a.CutByPoint(snake_b.pos_x, snake_b.pos_y);
      for (auto const &pt : temp) {
      	  grid_b.SetFood(pt.first, pt.second);
          grid_a.Clear(pt.first, pt.second);
      }
  }
  
  // Check snake_b safety
  if (grid_b.CrashBody(snake_a.pos_x, snake_a.pos_y)) {
      std::set<std::pair<int, int>> temp = snake_b.CutByPoint(snake_a.pos_x, snake_a.pos_y);
      food_from_b_for_a.insert(temp.begin(), temp.end());
      for (auto const &pt : temp) {
        grid_a.SetFood(pt.first, pt.second);
        grid_b.Clear(pt.first, pt.second);
      }
  }
  
  
  // Check if there's food over here
  if (snake_a.pos_x == food.x && snake_a.pos_y ==  food.y) {
  	  PlaceFood();
      snake_a.GrowBody();
      snake_a.SpeedUp();
  }
  if (snake_b.pos_x == food.x && snake_b.pos_y ==  food.y) {
  	  PlaceFood();
      snake_b.GrowBody();
      snake_b.SpeedUp();
  }
  
  if (grid_a.GetAt(snake_a.pos_x, snake_a.pos_y) == "Food") {
  	  snake_a.GrowBody();
      snake_a.SpeedUp();
      food_from_b_for_a.erase(std::pair(snake_a.pos_x, snake_a.pos_y));
  }
  
  if (grid_b.GetAt(snake_b.pos_x, snake_b.pos_y) == "Food") {
  	  snake_b.GrowBody();
      snake_b.SpeedUp();
      food_from_a_for_b.erase(std::pair(snake_b.pos_x, snake_b.pos_y));
  }
  
  grid_a.SetHead(snake_a.pos_x, snake_a.pos_y);
  grid_b.SetHead(snake_b.pos_x, snake_b.pos_y);
}


bool Game::CheckFoodPosition(int x, int y) {
	return grid_a.GetAt(x, y) == "Empty" && grid_b.GetAt(x, y) == "Empty";
}

void Game::PrintResultAccordingSize() {
  	if (snake_a.size() == snake_b.size()) {
    	std::cout << "A tie game! "<< "Both players get " << snake_a.size() << " scores." << "\n";
    } else if (snake_a.size() > snake_b.size()) {
    	std::cout << snake_a.name << " wins! " << snake_a.name << " gets " << snake_a.size() << " scores." << "\n";
    } else {
    	std::cout << snake_b.name << " wins! " << snake_b.name << " gets " << snake_b.size() << " scores." << "\n";
    }
}

void Game::PrintResultAccordingDeath() {
	if (!snake_a.alive) {
    	std::cout << snake_b.name << " wins! " << snake_a.name << " is dead!" << "\n";
    } else {
    	std::cout << snake_a.name << " wins! " << snake_b.name << " is dead!" << "\n";
    }
}
