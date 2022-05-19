#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned int max) {
	base_ = picture;
	max_ = max;
	size = 0;
	scene_ = new Image*[max_]();
	x_ = new unsigned int[max_]();
	y_ = new unsigned int[max_]();
}

StickerSheet::~StickerSheet() {
	clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
	if (this == &other) {
		return;
	} else {
		clear();
		copy(other);
	}
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
	if (this == &other) {
		return *this;
	} else {
		clear();
		copy(other);
	}
	return *this;
}

void StickerSheet::changeMaxStickers(unsigned int max) {
	Image** new_scene = new Image*[max]();
	unsigned int* x = new unsigned int[max]();
	unsigned int* y = new unsigned int[max]();
	unsigned int new_size = 0;
	for (unsigned int i = 0; i < max && i < size; i++) {
		new_scene[i] = new Image(*(scene_[i]));
		x[i] = x_[i];
		y[i] = y_[i];
		new_size++;
	}
	max_ = max;

	// reset variables
	clear();
	size = new_size;
	scene_ = new_scene;
	x_ = x;
	y_ = y;
}

int StickerSheet::addSticker(Image &sticker, unsigned int x, unsigned int y) {
	if (size == max_) {
		return -1;
	}
	scene_[size] = new Image(sticker);
	x_[size] = x;
	y_[size] = y;
	return size++;
}

bool StickerSheet::translate(unsigned int index, unsigned int x, unsigned int y) {
	if (index >= size) {
		return false;
	}
	x_[index] = x;
	y_[index] = y;
	return true;
}

void StickerSheet::removeSticker(unsigned int index) {
	if (index < size) {
		delete scene_[index];
		scene_[index] = NULL;

		// shift left
		for (unsigned int i = index; i < size - 1; i++) {
			scene_[i] = scene_[i+1];
			x_[i] = x_[i+1];
			y_[i] = y_[i+1];
		}
		x_[size-1] = 0;
		y_[size-1] = 0;
		scene_[size-1] = NULL;
		size--;
	}
}

Image* StickerSheet::getSticker(unsigned int index) {
	if (index < size) {
		return scene_[index];
	}
	return NULL;
}

Image StickerSheet::render() const {
	// Figure out render Image width and height
	unsigned int render_width = base_.width();
	unsigned int render_height = base_.height();

	for (unsigned int i = 0; i < size; i++) {
		unsigned int sticker_width = scene_[i]->width() + x_[i];
		if (sticker_width > render_width) {
			render_width = sticker_width;
		}

		unsigned int sticker_height = scene_[i]->height() + y_[i];
		if (sticker_height > render_height) {
			render_height = sticker_height;
		}
	}

	// resize new image
	Image renderImage = base_;
	renderImage.resize(render_width, render_height);

	// iterate through each sticker in scenes, then iterate through each pixel
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int x = 0; x < scene_[i]->width(); x++) {
			for (unsigned int y = 0; y < scene_[i]->height(); y++) {
				if ((scene_[i]->getPixel(x, y)).a != 0) {
					HSLAPixel& pixel = renderImage.getPixel(x_[i] + x, y_[i] + y);
					pixel = scene_[i]->getPixel(x, y);
				}
			}
		}
		// Make sure a != 0
		// Set pixel to new pixel
	}
	return renderImage;
}

void StickerSheet::clear() {
	for (unsigned int i = 0; i < size; i++) {
		delete scene_[i];
		scene_[i] = NULL;
	}
	size = 0;
	delete[] scene_;
	scene_ = NULL;
	delete[] x_;
	x_ = NULL;
	delete[] y_;
	y_ = NULL;
}

void StickerSheet::copy(const StickerSheet &other) {
	base_ = other.base_;
	max_ = other.max_;
	size = other.size;
	x_ = new unsigned int[max_]();
	y_ = new unsigned int[max_]();
	scene_ = new Image*[max_]();

	for (unsigned int i = 0; i < size; i++){
		scene_[i] = new Image(*(other.scene_[i]));
		x_[i] = other.x_[i];
		y_[i] = other.y_[i];
	}
}
