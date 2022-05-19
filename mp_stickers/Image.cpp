#include "Image.h"
using namespace cs225;

void Image::Image::lighten() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.l > 0.9) {
				pixel.l = 1;
			} else {
				pixel.l += 0.1;
			}
		}
	}
}

void Image::lighten(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.l > 1.0 - amount) {
				pixel.l = 1;
			} else {
				pixel.l += 0.1;
			}
			if (pixel.l < 0) {
				pixel.l = 0;
			}
		}
	}
}

void Image::darken() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.l < 0.1) {
				pixel.l = 0;
			} else {
				pixel.l -= 0.1;
			}
			if (pixel.l > 1) {
				pixel.l = 1;
			}
		}
	}
}

void Image::darken (double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.l < amount) {
				pixel.l = 0;
			} else {
				pixel.l -= amount;
			}
			if (pixel.l > 1) {
				pixel.l = 1;
			}
		}
	}
}

void Image::saturate() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.s > 0.9) {
				pixel.s = 1;
			} else {
				pixel.s += 0.1;
			}
			if (pixel.s < 0) {
				pixel.s = 0;
			}
		}
	}
}

void Image::saturate(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.s > 1 - amount) {
				pixel.s = 1;
			} else {
				pixel.s += amount;
			}
			if (pixel.s < 0) {
				pixel.s = 0;
			}
		}
	}
}

void Image::desaturate() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.s < 0.1) {
				pixel.s = 0;
			} else {
				pixel.s -= 0.1;
			}
			if (pixel.s > 1) {
				pixel.s = 1;
			}
		}
	}
}

void Image::desaturate(double amount) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			if (pixel.s < amount) {
				pixel.s = 0;
			} else {
				pixel.s -= amount;
			}
			if (pixel.s > 1) {
				pixel.s = 1;
			}
		}
	}
}

void Image::grayscale() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			pixel.s = 0;
		}
	}
}

void Image::rotateColor(double degrees) {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);
			pixel.h += degrees;
			while (pixel.h < 0) {
				pixel.h += 360;
			}
			while (pixel.h > 360) {
				pixel.h -= 360;
			}
		}
	}
}


void Image::illinify() {
	for (unsigned i = 0; i < width(); i++) {
		for (unsigned j = 0; j < height(); j++) {
			HSLAPixel &pixel = getPixel(i, j);

			double blue_a = std::abs(216 - pixel.h);
			double blue_b = 360 - blue_a;
			double orange_a = std::abs(11 - pixel.h);
			double orange_b = 360 - orange_a;

			double blue_min = 360;
			if (blue_a < blue_b) {
				blue_min = blue_a;
			} else {
				blue_min = blue_b;
			}

			double orange_min = 360;
			if (orange_a < orange_b) {
				orange_min = orange_a;
			} else {
				orange_min = orange_b;
			}

			if (orange_min < blue_min) {
				pixel.h = 11;
			} else {
				pixel.h = 216;
			}
		}
	}
}

void Image::scale(double factor) {
	PNG* old_image = new PNG(*this);
	resize(factor * width(), factor * height());
	for (unsigned i = 0; i < old_image->width(); i++) {
		for (unsigned j = 0; j < old_image->height(); j++) {
			getPixel(i * factor, j * factor) = old_image->getPixel(i, j);	
		}
	}
	delete old_image;
}

void Image::scale(unsigned w, unsigned h) {
	double w_factor = (double) w / width();
	double h_factor = (double) h / height();

	if (w_factor < h_factor) {
		scale(w_factor);
	} else {
		scale(h_factor);
	}
}
