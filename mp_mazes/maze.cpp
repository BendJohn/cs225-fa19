/* Your code here! */
#include "maze.h"

Cell::Cell() {
  right = true;
  down = true;
}

SquareMaze::~SquareMaze() {
  for (size_t i = 0; i < maze.size(); i++) {
	for (size_t j = 0; j < maze[i].size(); j++) {
		delete maze[i][j];
	}
  }
}

void SquareMaze::makeMazeHelper(int width, int height) {
  std::vector<std::vector<Cell*>> creating;
  for (int i = 0; i < height; i++) {
    std::vector<Cell*> tempRow;
    for (int j = 0; j < width; j++) {
      Cell* cell = new Cell();
      tempRow.push_back(cell);
    }
    creating.push_back(tempRow);
  }
  for (size_t i = 0; i < maze.size(); i++) {
	for (size_t j = 0; j < maze[i].size(); j++) {
		delete maze[i][j];
	}
  }
  maze = creating;
  mazeWidth = width;
  mazeHeight = height;
  dis.addelements(height*width);
}

SquareMaze::SquareMaze() {
  makeMazeHelper(4,4);
}

void SquareMaze::makeMaze(int width, int height) {
  makeMazeHelper(width, height);
  int currX = rand() % mazeWidth;
  int currY = rand() % mazeHeight;
  int bit = rand() % 2;
  while (dis.size(currY*mazeWidth+currX) < mazeWidth*mazeHeight) {
    if (bit == 0 && currX < mazeWidth-1 && (dis.find(currY*mazeWidth+currX) != dis.find(currY*mazeWidth+currX+1))) {
      dis.setunion(currY*mazeWidth+currX,currY*mazeWidth+currX+1);
      setWall(currX,currY,0,false);
    } else if (bit == 1 && currY < mazeHeight-1 && (dis.find(currY*mazeWidth+currX) != dis.find((currY+1)*mazeWidth+currX))) {
      dis.setunion(currY*mazeWidth+currX,(currY+1)*mazeWidth+currX);
      setWall(currX,currY,1,false);
    }
    currX = rand() % mazeWidth;
    currY = rand() % mazeHeight;
    bit = rand() % 2;
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  // If dir is right
  bool canTrav = false;
  if (dir == 0) {
    if (x < mazeWidth -1 && x >= 0 && y < mazeHeight && y >= 0 && !(maze[y][x]->right)) {
      canTrav = true;
    }
  } else if (dir == 1) {
    if (y < mazeHeight -1 && y >= 0 && x < mazeWidth && x >= 0 && !(maze[y][x]->down)) {
      canTrav = true;
    }
  } else if (dir == 2) {
    if (x > 0 && x < mazeWidth && y < mazeHeight && y >= 0 && !(maze[y][x-1]->right)) {
      canTrav = true;
    }
  } else {
    if (y > 0 && y < mazeHeight && x < mazeWidth && x >= 0 && !(maze[y-1][x]->down)) {
      canTrav = true;
    }
  }
  return canTrav;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if (!dir) {
      maze[y][x]->right = exists;
  } else {
      maze[y][x]->down = exists;
  }
}

int SquareMaze::getDir(int one_x, int one_y, int two_x, int two_y) {
  if (two_x > one_x) {
	return 0;
  }
  if (two_y > one_y) {
	return 1;
  }
  if (two_x < one_x) {
	return 2;
  }
  return 3;
}

std::vector<int> SquareMaze::solveMaze() {
  // Create a disjoint set of the maze with each coordinate holding:
  // int x coord of the parent (initialized to -1)
  // int y coord of the parent (initialized to -1)
  // int distance from origin (initialized to -1)
  std::vector<std::vector< std::pair<std::pair<int, int>, int> >> maze_traversal;
  for (int i = 0; i < mazeWidth; i++) {
	std::vector< std::pair<std::pair<int, int>, int> > tempRow;
	for (int j = 0; j < mazeHeight; j++) {
		tempRow.push_back(std::pair<std::pair<int, int>, int>(std::pair<int, int>(-1, -1), -1));
	}
	maze_traversal.push_back(tempRow);
  }
  makeTraverser(maze_traversal, 0, 0, 0, -1, -1);
  
  // Find largest bottom path pair
  std::pair<int, int> end_loc = std::pair<int, int>(0, mazeHeight - 1);
  int maxDist = maze_traversal[0][mazeHeight-1].second;
  for (int i = 0; i < mazeWidth; i++) {
	// Finding longest distance
	if (maxDist < maze_traversal[i][mazeHeight-1].second) {
		end_loc = std::pair<int, int>(i, mazeHeight - 1);
		maxDist = maze_traversal[i][mazeHeight-1].second;
	}
  }

  // Iterate through map and find solution vector
  std::vector<int> sol;
  while (end_loc != std::pair<int, int>(0, 0)) {
	std::pair<int, int> parent = maze_traversal[end_loc.first][end_loc.second].first;
  	sol.insert(sol.begin(), getDir(parent.first, parent.second, end_loc.first, end_loc.second));
	end_loc = parent;
  }

  return sol;
}

void SquareMaze::makeTraverser(std::vector<std::vector< std::pair<std::pair<int, int>, int> >>& maze_traversal, int x, int y, int dist, int prevX, int prevY) {
  // Base case, at leaf node or all directions are blocked or visited
  if ((!canTravel(prevX, prevY, getDir(prevX, prevY, x, y)) || maze_traversal[x][y].second > 0) && !(x == 0 && y == 0)) {
	return;
  }

  // Set distance and parent of this cell
  maze_traversal[x][y].second = dist;
  maze_traversal[x][y].first = std::pair<int, int>(prevX, prevY);

  // Recursive calls!
  makeTraverser(maze_traversal, x+1, y, dist+1, x, y);
  makeTraverser(maze_traversal, x-1, y, dist+1, x, y);
  makeTraverser(maze_traversal, x, y+1, dist+1, x, y);
  makeTraverser(maze_traversal, x, y-1, dist+1, x, y);
}

cs225::PNG* SquareMaze::drawMaze() const {
  cs225::PNG* toReturn = new cs225::PNG(mazeWidth*10 + 1, mazeHeight*10+1);
  for (unsigned i = 10; i < toReturn->width(); i++) {
    cs225::HSLAPixel& hsla = toReturn->getPixel(i,0);
    hsla.l = 0;
    hsla.h = 150;
  }
  for (unsigned j = 0; j < toReturn->height(); j++) {
    cs225::HSLAPixel& hsla = toReturn->getPixel(0,j);
    hsla.l = 0;
    hsla.h = 320;
  }
  for (unsigned y = 0; y < maze.size(); y++) {
    for (unsigned x = 0; x < maze[y].size(); x++) {
      if (maze[y][x]->right) {
        for (unsigned k = 0; k < 11; k++) {
          cs225::HSLAPixel& hsla = toReturn->getPixel((x+1)*10,y*10+k);
          hsla.l = 0;
        }
      }
      if (maze[y][x]->down) {
        for (unsigned k = 0; k < 11; k++) {
          cs225::HSLAPixel& hsla = toReturn->getPixel(x*10+k,(y+1)*10);
          hsla.l = 0;
        }
      }
    }
  }
  return toReturn;
}

cs225::PNG* SquareMaze::drawMazeWithSolution() {
  cs225::PNG* toReturn = drawMaze();
  std::vector<int> sol = solveMaze();
  std::pair<int,int> pix = std::pair<int,int>(5,5);
  for (unsigned i = 0; i < sol.size(); i++) {
    if (sol[i] == 0) {
      for (int j = 0; j < 10; j++) {
        cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
        currPixel.h = 0;
        currPixel.s = 1;
        currPixel.l = 0.5;
        currPixel.a = 1;
        pix.first++;
      }
    } else if (sol[i] == 1) {
      for (int j = 0; j < 10; j++) {
        cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
        currPixel.h = 0;
        currPixel.s = 1;
        currPixel.l = 0.5;
        currPixel.a = 1;
        pix.second++;
      }
    } else if (sol[i] == 2) {
      for (int j = 0; j < 10; j++) {
        cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
        currPixel.h = 0;
        currPixel.s = 1;
        currPixel.l = 0.5;
        currPixel.a = 1;
        pix.first--;
      }
    } else {
      for (int j = 0; j < 10; j++) {
        cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
        currPixel.h = 0;
        currPixel.s = 1;
        currPixel.l = 0.5;
        currPixel.a = 1;
        pix.second--;
      }
    }
  }
  cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
  currPixel.h = 0;
  currPixel.s = 1;
  currPixel.l = 0.5;
  currPixel.a = 1;
  pix.first -= 4;
  pix.second +=5;
  for (int k = 0; k < 9; k++) {
    cs225::HSLAPixel& currPixel = toReturn->getPixel(pix.first, pix.second);
    currPixel.l = 1;
    pix.first++;
  }
  return toReturn;
}


cs225::PNG* SquareMaze::drawCreative() const {
  cs225::PNG* toReturn = drawMaze();

  for (size_t i = 0; i < toReturn->height()/3; i++) {
    for (size_t j = toReturn->width()/5; j < 4*toReturn->width()/5; j++) {
	cs225::HSLAPixel& currPixel = toReturn->getPixel(i, j);
	currPixel.l = 1;
    }
  }

  for (size_t i = 2*toReturn->height()/3; i < toReturn->height(); i++) {
    for (size_t j = toReturn->width()/5; j < 4*toReturn->width()/5; j++) {
	cs225::HSLAPixel& currPixel = toReturn->getPixel(i, j);
	currPixel.l = 1;
    }
  }

  int count = 0;
  for (size_t i = 0; i < toReturn->height(); i++) {
    for (size_t j = 0; j < toReturn->width(); j++) {
	count++;
	cs225::HSLAPixel& currPixel = toReturn->getPixel(i, j);
	if (currPixel.l == 0) {
		currPixel.l = 0.5;
		if (toReturn->height() * toReturn->width() / count % 5 == 0) {
			currPixel.h = 72;
		}
		if (toReturn->height() * toReturn->width() / count % 5 == 1) {
			currPixel.h = 72 * 2;
		}
		if (toReturn->height() * toReturn->width() / count % 5 == 2) {
			currPixel.h = 72 * 3;
		}
		if (toReturn->height() * toReturn->width() / count % 5 == 3) {
			currPixel.h = 72 * 4;
		}
		if (toReturn->height() * toReturn->width() / count % 5 == 4) {
			currPixel.h = 72 * 5;
		}
	}
    }
  }

  return toReturn;
}
