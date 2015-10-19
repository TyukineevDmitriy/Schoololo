#pragma once

//Allegro libraries
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
//#include <allegro5\allegro_ttf.h>
//#include <allegro5\allegro_native_dialog.h>
//#include <allegro5\allegro_primitives.h>
//#include <allegro5\allegro_image.h>

#include <random>
//#include <math.h>

//Colors
#define ACOLOR_RED al_map_rgb(255, 0, 0)
#define ACOLOR_BLUE al_map_rgb(0, 0, 255)
#define ACOLOR_CYAN al_map_rgb(10, 180, 255)
#define ACOLOR_BLACK al_map_rgb(0, 0, 0)
#define ACOLOR_WHITE al_map_rgb(255, 255, 255)
#define ACOLOR_GREEN al_map_rgb(0, 255, 0)
#define ACOLOR_ORANGE al_map_rgb(255, 127, 0)
#define ACOLOR_MAGENTA al_map_rgb(255, 0, 255)
#define ACOLOR_YELLOW al_map_rgb(255, 255, 0)
#define ACOLOR_GRAY al_map_rgb(127, 127, 127)
#define ACOLOR_BROWN al_map_rgb(120, 70, 20)

#define ACOLOR_SANDS al_map_rgb(244, 164, 96)

//Fonts
#define AFONT_USUAL 0
#define AFONT_I 1
#define AFONT_JOK 2

#define FONT_STAND_SIZE 25

//Alignment
#define AALIGN_CENTER ALLEGRO_ALIGN_CENTRE
#define AALIGN_LEFT ALLEGRO_ALIGN_LEFT
#define AALIGN_RIGHT ALLEGRO_ALIGN_RIGHT

using namespace std;

extern int screen_width;
extern int screen_height;
extern int screen_center;
extern int screen_middle;
extern int FPS;

bool InitAllegroModules(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_EVENT_QUEUE* event_queue);

void InitFonts();

ALLEGRO_FONT* ResolveFont(int fontName);

void ClearScr();

void SetBackground(ALLEGRO_COLOR color);

void Show(double restTime = 0);

void Print(char* text, ALLEGRO_COLOR color, int font, int x, int y, int alignment = AALIGN_LEFT);

template <typename... Args> 
void Print(char* text, ALLEGRO_COLOR color, int font, int x, int y, int alignment, const Args&... args) {
	//Resolve font from int to ALLEGRO_FONT
	ALLEGRO_FONT* text_font = ResolveFont(font);
		
	al_draw_textf(text_font, color, x, y, alignment, text, args...);	
}
	
void DrawLine(int fromX, int fromY, int toX, int toY, ALLEGRO_COLOR color, int thickness);

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, ALLEGRO_COLOR color, int thickness = 0);

void DrawRectangle(int fromX, int fromY, int toX, int toY, ALLEGRO_COLOR color, int thickness = 0, int radiusX = 0, int radiusY = 0);

void DrawCircle(int centerX, int centerY, int radius, ALLEGRO_COLOR color, int thickness = 0);

void DrawEllipse(int centerX, int centerY, int radiusX, int radiusY, ALLEGRO_COLOR color, int thickness = 0);

ALLEGRO_BITMAP* CreateBitmap(string path, int* width, int* height);

void DrawImage(ALLEGRO_BITMAP* img, int posX, int posY);

void DrawImage(ALLEGRO_BITMAP* img, int posX, int posY, bool flipHor);

void DrawImage(ALLEGRO_BITMAP* img, int posX, int posY, int imgWidth, int imgHeight, int angle);

void SetImageMask(ALLEGRO_BITMAP* img, ALLEGRO_COLOR color);

double Rand();

int Rand(int from, int to);

	
//void lala(ALLEGRO_DISPLAY* display);