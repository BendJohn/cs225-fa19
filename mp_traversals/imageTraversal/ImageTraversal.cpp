#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal(NULL), doneFlag(true) {
  /** @todo [Part 1] */
}

/**
 * Two parameter constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal* traversal, Point start, double tolerance, PNG png) : traversal(traversal), start(start), tolerance(tolerance), png(png) {
  visited.resize(png.width(), std::vector<bool>(png.height(), false));
  visited[start.x][start.y] = true;

  current = traversal->peek();
  doneFlag = false;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point temp = traversal->pop();
  visited[temp.x][temp.y] = true;

  // Check right
  Point right(temp.x + 1, temp.y);
  if (right.x < png.width() && calculateDelta(png.getPixel(right.x, right.y), png.getPixel(start.x, start.y)) < tolerance) {
	traversal->add(right);
  }

  // Check below
  Point below(temp.x, temp.y + 1);
  if (below.y < png.height() && calculateDelta(png.getPixel(below.x, below.y), png.getPixel(start.x, start.y)) < tolerance) {
	traversal->add(below);
  }

  // Check left
  Point left(temp.x - 1, temp.y);
  if (temp.x > 0 && calculateDelta(png.getPixel(left.x, left.y), png.getPixel(start.x, start.y)) < tolerance) {
	traversal->add(left);
  }

  // Check above
  Point above(temp.x, temp.y - 1);
  if (temp.y > 0 && calculateDelta(png.getPixel(above.x, above.y), png.getPixel(start.x, start.y)) < tolerance) {
	traversal->add(above);
  }

  if (traversal->empty()) { doneFlag = true; }
  else {
	current = traversal->peek();
	while (visited[current.x][current.y]) {
		traversal->pop();
		if (traversal->empty()) {
			doneFlag = true;
			break;
		}
		current = traversal->peek();
	}
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(other.doneFlag == doneFlag);
}

