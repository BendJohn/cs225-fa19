
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG geomet;
  geomet.readFromFile("images/geomet.png");

  FloodFilledImage img(geomet);

  BFS bfs1(geomet, Point(geomet.width()/2, geomet.height()/2), 1); 
  DFS dfs1(geomet, Point(geomet.width()*2/3, geomet.height()/2), 1);

  MyColorPicker color;

  img.addFloodFill(bfs1, color);

  Animation animation = img.animate(10000);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
