#pragma once

#include <deque>
#include <algorithm>

#include "GameObject.h"
#include "ClassFactory.h"
#include "AleInterf.h"
#include "Camera.h"
#include "EventSlot.h"
#include "GraphKeeper.h"
#include "ConfigReader.h"
#include "LuaS.h"

/* Game Content */
#include "Actor.h"
#include "Monster.h"
#include "WallObject.h"





class Level : public GameObject {
public:

	Level() { }

	//just debug info. To delete 
	int npcAmount = 0;
	int objectsOnScreen = 0;

	bool LevelLoaderInit() {
		//Declare classes in factories
		factoryStatic.AddClass<WallObject>("Wall");

		factoryMoving.AddClass<Actor>("Actor");
		factoryMoving.AddClass<Monster>("Monster");

		return true;
	}

	virtual void Tick(float dt) override {
		//Private tick of each object
		for (const auto& slot : container) {
			if (slot->TickEvent)
				slot->obj->Tick(dt);
		}

		camera->Tick();
	}

	virtual void Render(float, float) override {
		//static float x, y;
		//static float objX, objY;
		const Point& cameraPos = camera->GetCameraPosition();

		objectsOnScreen = 0;

		deque<EventSlot*>* renderedObjects = camera->GetObjectsInsideCam(container);

		//Private render for each object
		for (const auto& slot : (*renderedObjects)) {
			slot->obj->Render(cameraPos.x, cameraPos.y);
			objectsOnScreen++;
		}

		delete renderedObjects;
	}

	virtual void KeyResolve(int key, bool pressed) override {
		//Private key handling of each object
		for (const auto& slot : container) {
			if (slot->KeyEvent)
				slot->obj->KeyResolve(key, pressed);
		}

		if (key == ALLEGRO_KEY_1 && pressed) {
			for (int i = 0; i < 1000; i++) {
				SpawnObject("Zombie1");
			}
		} else if (key == ALLEGRO_KEY_0 && pressed) {
			SpawnObject("Actor");
		}

	}

	bool LoadLevel() {

		//Reading level from configs...

		SetBackground(ACOLOR_BROWN);

		player = (Actor*)SpawnObject("Actor");

		camera = new Camera(player, screen_width, screen_height);

		return false;
	}

private:

	LuaS& lua = *(LuaS::Get());
	GraphKeeper& graphKeeper = *(GraphKeeper::Get());
	ConfigReader& cfgReader = *(ConfigReader::Get());

	deque<EventSlot*> container;
	//deque<EventSlot*> collideObjs;

	ClassFactory<WallObject, int, int> factoryStatic;
	ClassFactory<WallObject, int, int, int> factoryMoving;

	Actor* player;
	Camera* camera;

	WallObject* SpawnObject(string objectName) {
		//Should take configs from cfgs
		string className = cfgReader.GetStrParam(objectName, "class");
		int speed = cfgReader.GetIntParam(objectName, "speed");

		//It should be taken from Spawner file
		int x = 300;
		int y = 300;

		WallObject* obj;

		//If the object has speed, then it's stored in factoryMoving
		if (speed) {
			obj = factoryMoving.Get(className)(x, y, speed);
		}
		//else it's stored in factoryStatic
		else {
			obj = factoryStatic.Get(className)(x, y);
		}

		//Get amount of GRAPHIC items (anims, images) that are necessary for this game object
		lua.LoadStr("GetContentAmount");
		lua.PushArgument<string>(objectName);
		lua.Exec(1, 1);
		int itemsAmount = lua.GetArgument<int>(-1);

		//Init all graphic items
		for (int i = 1; i <= itemsAmount; i++) {
			//Get item name
			lua.LoadStr("GetItemName");
			lua.PushArgument<string>(objectName);
			lua.PushArgument<int>(i);
			lua.Exec(2, 2);
			string stateName = lua.GetArgument<string>(-2);
			string itemName = lua.GetArgument<string>(-1);

			obj->InitClip(stateName, graphKeeper.CreateClip(itemName));
		}

		//Setting position
		//newGObject->SetPosition(Rand(0, screen_width), Rand(0, screen_height));

		//Init a new Event slot for the object
		EventSlot* newSlot = new EventSlot(true, true, true);
		newSlot->obj = obj;//newGObject;
		container.push_back(newSlot);

		npcAmount++;

		return obj;
	}

	

};