#pragma once

class GameObject;

struct EventSlot {
	GameObject* obj;
	bool TickEvent = false;
	bool KeyEvent = false;
	bool RenderEvent = false;

	EventSlot(bool tick, bool key, bool render) {
		TickEvent = tick;
		KeyEvent = key;
		RenderEvent = render;
	}

};