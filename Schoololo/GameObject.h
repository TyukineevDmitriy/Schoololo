#pragma once

//#include <map>

//#include "EventSlot.h"
//#include "Clip.h"
#include "Point.h"

using namespace std;

class GameObject {
public:

	GameObject() {}

	//virtual void InitClip(const string& state, Clip* clip) = 0;

	/*void GetPosition(int* x, int* y) {
	*x = this->x;
	*y = this->y;
	}*/

	//void SetEventSlot(const EventSlot* slot) {	}

	virtual void Tick(float dt) {}

	virtual void Render(float x, float y) {}

	virtual void KeyResolve(int key, bool pressed) {}

	//virtual void Collide(GameObject* other) {}

	const Point& GetPosition() {
		return pos;
	}

protected:

	Point pos;

	//Clip* curClip;

	//enum states { };

	//int state;;
	
	//map<int, Clip*> clip;
	

	//EventSlot* mySlot;
	//map<string, Image*> images;

	/*void SetState(int newState) {
		state = newState;
	}*/

};