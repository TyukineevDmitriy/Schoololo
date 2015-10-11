#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

//#include <typeinfo>
#include <ctime>
#include <deque>

#include "AleInterf.h"
#include "EventSlot.h"
//#include "GameObject.h"
#include "GraphKeeper.h"
#include "LuaS.h"
#include "ConfigReader.h"
#include "Level.h"

using namespace std;

//typedef void(*PFunctionVoid)();
//typedef void(*PFunctionInt)(int a);

class Core {
private:

	LuaS& lua = *(LuaS::Get());
	GraphKeeper& graphKeeper = *(GraphKeeper::Get());
	ConfigReader& cfgReader = *(ConfigReader::Get());

	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* eventsQ;

	Level level;

	float FPStime = 0;

	void Update() {
		bool redraw = true;
		float deltaTime = 0;
		clock_t lastTime = clock(); //Measured in seconds

		//int frames = 0;
		ALLEGRO_EVENT e;

		//this->container = &container;

		while (1/*updating*/) {
			//Take next event from the events queue
			al_wait_for_event(eventsQ, &e);

			/************ KEY HANDLER ************/
			if (e.type == ALLEGRO_EVENT_KEY_DOWN) {
				//Check if we have to close the game
				if (e.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
					break;
				}

				//Common keyboard handling
				CommonKeyHandler(e.keyboard.keycode, true);

				//Private keyboard handling (for each object in the level)
				level.KeyResolve(e.keyboard.keycode, true);

			} else if (e.type == ALLEGRO_EVENT_KEY_UP) {
				//Common keyboard handling
				CommonKeyHandler(e.keyboard.keycode, false);

				//Private keyboard handling (for each object in the level)
				level.KeyResolve(e.keyboard.keycode, false);

			} else if (e.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			
			/************ TIMER HANDLER ************/
			} else if (e.type == ALLEGRO_EVENT_TIMER) {
				deltaTime = (float)(clock() - lastTime) / CLOCKS_PER_SEC;
				lastTime = clock();
				//Common tick
				CommonTick(deltaTime);

				//Private tick (for each object on the level)
				level.Tick(deltaTime);

				//If Tick was we should redraw the changes
				redraw = true;
			}

			/************ RENDER ************/
			if (redraw && al_is_event_queue_empty(eventsQ)) {
				ClearScr();

				//Private render (for each object on the level)
				level.Render(0, 0);

				//Common render
				CommonRender();

				//Output the graphic onto display
				Show();

				redraw = false;
			}
		}

		//When the loop ends, the game's closing
		EndGame();
	}

	void CommonTick(float dt) {
		FPStime += dt;
	}

	void CommonKeyHandler(int key, bool pressed) {
		
	}

	void CommonRender() {
		static float FPS = 0;
		static float counts = 1.0;
		if (FPStime > 0.5) {
			FPS = counts / FPStime;
			FPStime = 0;
			counts = 1.0;
		} else {
			counts += 1.0;
		}

		Print("NPC: %d", ACOLOR_WHITE, AFONT_I, 10, 10, 0, level.npcAmount);
		Print("ON_SCREEN: %d", ACOLOR_BLACK, AFONT_USUAL, 10, 40, 0, level.objectsOnScreen);
		Print("FPS: %f", ACOLOR_BLACK, AFONT_USUAL, 10, 70, 0, FPS);
		
		
		//Print("Dt: %lf", ACOLOR_WHITE, AFONT_USUAL, 550, 10, 0, deltaTime);
	}

	void CloseAllegro() {
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(eventsQ);
	}

	void EndGame() {
		CloseAllegro();
		lua.Close();
		graphKeeper.ClearContainer();
		//close level
	}

public:

	Core() {
		//Launch allegro and checking for errors
		if (!al_init()) {
			al_show_native_message_box(NULL, "Error", "", "Failed to init allegro", NULL, NULL);
			Show(2);
			//return false;
		}

		//Creating display
		display = al_create_display(screen_width, screen_height);
		if (!display) {
			al_show_native_message_box(NULL, "Error", "", "Failed to init display", NULL, NULL);
			Show(2);
			//return false;
		}

		timer = al_create_timer(1.0 / FPS);
		if (!timer) {
			al_show_native_message_box(NULL, "Error", "", "Failed to init timer", NULL, NULL);
			//Print("%s, failed to create timer!\n", ACOLOR_RED, AFONT_I, screen_center, screen_middle, AALIGN_CENTER, stderr);
			Show(2);
			//return false;
		}

		timer = al_create_timer(1.0 / FPS);
		//Init Events
		eventsQ = al_create_event_queue();
		if (!eventsQ) {
			al_show_native_message_box(NULL, "Error", "", "Failed to create event_queue!", NULL, NULL);
			//stderr?
		}

		InitAllegroModules(display, timer, eventsQ);
	}

	void StartGame() {
		lua.LoadFile("scripts/NPCai.lua");
		lua.Exec(0, 0);
		lua.LoadFile("scripts/imagesPath.lua");
		lua.Exec(0, 0);

		lua.LoadStr("SetDefaults");
		lua.PushArgument<int>(screen_width);
		lua.PushArgument<int>(screen_height);
		lua.Exec(2, 0);

		if (!level.LevelLoaderInit()) {
			//ERROR of loading level!!!!!!!!
		}

		if (!level.LoadLevel()) {
			//ERROR of loading level!!!!!!!!
		}

		Update();
	}

	

};
