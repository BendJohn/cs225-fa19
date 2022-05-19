#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG input, output;
  input.readFromFile(inputFile);
  output.readFromFile(inputFile);

  for (size_t x = 0; x < input.width(); x++) {
    for (size_t y = 0; y < input.height(); y++) {
      // Get pixels to perform rotation
      cs225::HSLAPixel & output_pixel = output.getPixel(output.width() - x - 1, output.height() - y - 1);
      cs225::HSLAPixel & input_pixel = input.getPixel(x, y);

      // Perform rotation
      output_pixel.h = input_pixel.h;
      output_pixel.s = input_pixel.s;
      output_pixel.l = input_pixel.l;
      output_pixel.a = input_pixel.a;
    }
  }
  // Write to file
  output.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (size_t x = 0; x < png.width(); x++) {
    for (size_t y = 0; y < png.height(); y++) {
      cs225::HSLAPixel & pixel = png.getPixel(x, y);

      if (x < png.width() / 2 && y < png.height() / 2) {
        pixel.h = x * 360 / (png.width() / 2);
        pixel.s = y / (png.height() / 2);
        pixel.l = 0.5;
        pixel.a = 1;
      }
      if (x < png.width() / 2 && y > png.height() / 2) {
        pixel.h = x * 360 / (png.width() / 2);
        pixel.s = 1 -  (y - png.height() / 2) / (png.height() / 2);
        pixel.l = 0.5;
        pixel.a = 1;
      }
      if (x > png.width() / 2 && y < png.height() / 2) {
        pixel.h = 360 - x * 360 / (png.width());
        pixel.s = y / (png.height() / 2);
        pixel.l = 0.5;
        pixel.a = 1;
      }
      if (x > png.width() / 2 && y > png.height() / 2) {
        pixel.h = 360 - x * 360 / (png.width());
        pixel.s = 1 - (y - png.height() / 2) / (png.height() / 2);
        pixel.l = 0.5;
        pixel.a = 1;
      }
    }
  }
  return png;
}
