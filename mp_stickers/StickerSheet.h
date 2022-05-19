/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
using namespace cs225;

class StickerSheet {
	Image** scene_;
	Image base_;
	unsigned int* x_;
	unsigned int* y_;
	unsigned int max_;
	unsigned int size;

	void clear();
	void copy(const StickerSheet &other);

	public:
	StickerSheet(const Image &picture, unsigned int max);
	~StickerSheet();
	StickerSheet(const StickerSheet &other);

	const StickerSheet& operator=(const StickerSheet &other);
	void changeMaxStickers(unsigned int max);
	int addSticker(Image &sticker, unsigned int x, unsigned int y);
	bool translate(unsigned int index, unsigned int x, unsigned int y);
	void removeSticker(unsigned int index);
	Image* getSticker(unsigned int index);
	Image render() const;
}; 
