//#include "AleInterf.h"
//#include "Core.h"
//
//void Core::StartGame() {
//	lua.LoadFile("script.lua");
//	lua.Exec(0, 0);
//
//	lua.LoadStr("SetDefaults");
//	lua.PushArgument<int>(screen_width);
//	lua.PushArgument<int>(screen_height);
//	lua.Exec(2, 0);
//
//	SetBackground(ACOLOR_GRAY);
//	Update();
//}