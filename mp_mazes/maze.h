/* Your code here! */
#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>
#include <random>

class Cell {
public:
  Cell();
  bool down;
  bool right;
};

class SquareMaze {
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dir, bool exists);
  std::vector<int> solveMaze();
  cs225::PNG* drawMaze() const;
  cs225::PNG* drawCreative() const;
  cs225::PNG* drawMazeWithSolution();
  ~SquareMaze();
private:
  int getDir(int one_x, int one_y, int two_x, int two_y);
  void makeTraverser(std::vector<std::vector< std::pair<std::pair<int, int>, int> >>& maze_traversal, int x, int y, int dist, int prevX, int prevY);
  void makeMazeHelper(int width, int height);
  std::vector<std::vector<Cell*>> maze;
  DisjointSets dis;
  int mazeHeight;
  int mazeWidth;
};
