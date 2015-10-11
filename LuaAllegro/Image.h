#pragma once
#include <allegro5\allegro.h>

class Image {
public:

	ALLEGRO_BITMAP* image;
	int width;
	int height;

	Image(ALLEGRO_BITMAP* imgPointer, int* width, int* height) {
		image = imgPointer;
		this->width = *width;
		this->height = *height;
	}
};