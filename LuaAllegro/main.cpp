//#include <deque>

//#include "AleInterf.h"
#include "Core.h"

int main(void) {
	Core gameCore;
	gameCore.StartGame();
	
	return 0;
}

//void KeyResolve(int key) {
//	//Create a new NPC
//	if (key == ALLEGRO_KEY_1) {
//		NPC* newNPC = new NPC(container.size());
//		newNPC->InitImages(graphKeeper.AddImage(IMG_ID_NPC, IMG_PATH_NPC), graphKeeper.AddImage(IMG_ID_DEAD, IMG_PATH_DEAD), graphKeeper.AddImage(IMG_ID_SHOOT, IMG_PATH_SHOOT));
//		newNPC->SetPosition(al.Rand(10, al.screen_width - 10), al.Rand(10, al.screen_height - 10), true);
//
//		EventSlot* newSlot = new EventSlot(true, true, true);
//		newSlot->obj = newNPC;
//
//		container.push_back(newSlot);
//
//		//Add NPC into Lua's container
//		lua.LoadStr("addNPC");
//		lua.PushArgument<int>(container.size() - 1);
//		lua.Exec(1, 0);
//	} else if (key == ALLEGRO_KEY_A) {
//
//	}
//}