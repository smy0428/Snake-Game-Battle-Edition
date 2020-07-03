#include "grid.h"
#include <vector>
#include <string>


Grid::Grid(int w, int h) { grid = std::vector(h, std::vector<std::string> (w, "Empty")); }

void Grid::Clear(int x, int y) { grid[y][x] = "Empty"; }

void Grid::SetHead(int x, int y) { grid[y][x] = "Head"; }

void Grid::SetBody(int x, int y) { grid[y][x] = "Body"; }

void Grid::SetFood(int x, int y) { grid[y][x] = "Food"; }

bool Grid::CrashBody(int x, int y) { grid[y][x] == "Body"; }

std::string Grid::GetAt(int x, int y) { return grid[y][x]; }