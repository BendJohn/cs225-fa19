/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // Create necessary variables
    MosaicCanvas* retCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> kdtree_vec;
    map<Point<3>, TileImage*> point2Tile;

    // Create kdtree_vec to create kdtree of tileImages (as points)
    for (unsigned i = 0; i < theTiles.size(); i++) {
	// Get average color of each tileImage as a point
	LUVAPixel avgPixel = theTiles[i].getAverageColor();
	Point<3> avgPixelPt = convertToXYZ(avgPixel);

	// Push this avg point into our helpful data structures
	kdtree_vec.push_back(avgPixelPt);
	point2Tile.insert(pair<Point<3>, TileImage*>(avgPixelPt, &theTiles[i]));
    }
    KDTree<3> tileImageTree(kdtree_vec);

    // Iterate through source image and make it into a mosaic
    for (int i = 0; i < theSource.getRows(); i++) {
	for (int j = 0; j < theSource.getColumns(); j++) {
		// Find closest tile based on pixel
		LUVAPixel curr_pixel = theSource.getRegionColor(i, j);
		Point<3> query = convertToXYZ(curr_pixel);
		Point<3> pt = tileImageTree.findNearestNeighbor(query);
		TileImage* curr_tile = point2Tile[pt];

		// Insert it into the canvas!
		retCanvas->setTile(i, j, curr_tile);
	}
    }
    return retCanvas;
}

