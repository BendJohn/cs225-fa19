#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
	Image scary_bg, thought, bj_profile, shrek;
	scary_bg.readFromFile("Images/scary_bg.png");
	shrek.readFromFile("Images/shrek.png");
	bj_profile.readFromFile("Images/bj_profile.png");
	thought.readFromFile("Images/thought.png");

	StickerSheet sheet(scary_bg, 5);
	sheet.addSticker(thought, 150, scary_bg.height() - 550);
	sheet.addSticker(shrek, 500, scary_bg.height() - 480);
	sheet.addSticker(bj_profile, 0, scary_bg.height() - 400);

  Image rendered = sheet.render();
  rendered.writeToFile("myImage.png");

  return 0;
}
