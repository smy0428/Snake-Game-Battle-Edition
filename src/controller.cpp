#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

//Controller::Controller(): m_keystates(0) {}
//Controller::~Controller() { delete m_keystates; }

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size() == 0) {
      snake.direction = input;
  	  return;
  }

}

// handle input with only 4 directions
/*
void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}
*/

// handle input with diagonal directions
/*
void Controller::HandleInput(bool &running, Snake &snake) const {
  	SDL_Event e;
    while (SDL_PollEvent(&e)) {
      	if (e.type == SDL_QUIT) {
          	running = false;
      } else if (e.type == SDL_KEYDOWN) {
          	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
            if (keystates[SDL_SCANCODE_ESCAPE]) {
                running = false;
            } else {
                auto up = keystates[SDL_SCANCODE_UP];
                auto down = keystates[SDL_SCANCODE_DOWN];
                auto left = keystates[SDL_SCANCODE_LEFT];
                auto right = keystates[SDL_SCANCODE_RIGHT];
                auto numKeysPressed = up + down + left + right;

                // only one key has been pressed
                if (numKeysPressed == 1) {
                    if (up) {
                        ChangeDirection(snake, Snake::Direction::kUp,
                                        Snake::Direction::kDown);
                    } else if (down) {
                        ChangeDirection(snake, Snake::Direction::kDown,
                                        Snake::Direction::kUp);
                    } else if (left) {
                        ChangeDirection(snake, Snake::Direction::kLeft,
                                        Snake::Direction::kRight);
                    } else {
                        ChangeDirection(snake, Snake::Direction::kRight,
                                        Snake::Direction::kLeft);
                    }
                }
                if (numKeysPressed == 2) {
                    if (up && left) {
                        ChangeDirection(snake, Snake::Direction::kUpLeft, 
                                        Snake::Direction::kDownRight);
                    } else if (down && right) {
                        ChangeDirection(snake, Snake::Direction::kDownRight, 
                                        Snake::Direction::kUpLeft);
                    } else if (up && right) {
                        ChangeDirection(snake, Snake::Direction::kUpRight, 
                                        Snake::Direction::kDownLeft);
                    } else if (down && left) {
                        ChangeDirection(snake, Snake::Direction::kDownLeft, 
                                        Snake::Direction::kUpRight);
                    }
                }
            }
        }
    }
}
*/
// two players version    
void Controller::HandleInput(bool &running, Snake &snake_a, Snake &snake_b) const {
  	SDL_Event e;
    while (SDL_PollEvent(&e)) {
      	if (e.type == SDL_QUIT) {
          	running = false;
      } else if (e.type == SDL_KEYDOWN) {
          	const Uint8 *keystates = SDL_GetKeyboardState(NULL);
            if (keystates[SDL_SCANCODE_ESCAPE]) {
                running = false;
            } else {
              	HandleInputOnSnake(snake_a, keystates, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
              	HandleInputOnSnake(snake_b, keystates, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
                //HandleInputOnSnake(snake_b, keystates, SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J, SDL_SCANCODE_L);
        	}
    	}
	} 
}

void Controller::HandleInputOnSnake(Snake &snake, const Uint8 *keystates, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right) const {
    auto uState = keystates[up];
    auto dState = keystates[down];
    auto lState = keystates[left];
    auto rState = keystates[right];
    auto states = uState + dState + lState + rState;
    // only one key has been pressed
    if (states == 1) {
        if (uState) {
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
        } else if (dState) {
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
        } else if (lState) { 
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
        } else {
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
        }
    }
    if (states == 2) {
        if (uState && lState) {
          ChangeDirection(snake, Snake::Direction::kUpLeft, 
                          Snake::Direction::kDownRight);
        } else if (dState && rState) {
          ChangeDirection(snake, Snake::Direction::kDownRight, 
                          Snake::Direction::kUpLeft);
        } else if (uState && rState) {
          ChangeDirection(snake, Snake::Direction::kUpRight, 
                          Snake::Direction::kDownLeft);
        } else if (dState && lState) {
          ChangeDirection(snake, Snake::Direction::kDownLeft, 
                          Snake::Direction::kUpRight);
        }
    }
}   
      
      