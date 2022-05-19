#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze creative;
    creative.makeMaze(50,50);
    cs225::PNG* myMaze = creative.drawCreative();
    myMaze->writeToFile("creative.png");
    delete myMaze;
    return 0;
}
