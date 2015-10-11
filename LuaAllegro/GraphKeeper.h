#pragma once
#include <map>
#include <string>

#include "Image.h"
#include "AleInterf.h"
#include "LuaS.h"
#include "Animation.h"
#include "Clip.h"

using namespace std;

class GraphKeeper {
public:

	GraphKeeper() { }

	static GraphKeeper* Get() {
		static GraphKeeper instance;
		return &instance;
	}

	/*Image* GetImage(string id, string mask) {
		//If the neccessary image has not been initialized, then lets initialize it
		if (!imgContainer[id]) {
			int width;
			int height;
			Image* newImg = new Image(CreateImage(GetImagePath(id), &width, &height), &width, &height);
			SetImageMask(newImg->image, ResolveMaskColor(mask));

			imgContainer[id] = newImg;
		}
		return imgContainer[id];
	}*/

	Clip* CreateClip(string itemName) {
		if (!animContainer[itemName] && !imgContainer[itemName]) {
			//Get info (number of frames and path) from lua
			lua.LoadStr("GetItemInfo");
			lua.PushArgument<string>(itemName);
			lua.Exec(1, 3);
			int imagesAmount = lua.GetArgument<int>(-3);
			string rootPath = lua.GetArgument<string>(-2);
			int frameRate = lua.GetArgument<int>(-1);

			if (imagesAmount == 1) {
				rootPath += itemName + ".png";
				
				//Creating new image
				imgContainer[itemName] = CreateImage(rootPath);
			} else {
				//Creating new animation

				//Create and fill a row of images
				deque<Image*> imgRow;
				for (int i = 1; i <= imagesAmount; i++) {
					string path = rootPath + itemName + "_0000" + to_string(i) + ".png";
					imgRow.push_back(CreateImage(path));
				}

				Animation* newAnim = new Animation(imgRow, frameRate);
				animContainer[itemName] = newAnim;
			}
		}

		if (animContainer[itemName]) {
			return new Clip(animContainer[itemName]);
		} else {
			return new Clip(imgContainer[itemName]);
		}
		return NULL;
	}

	/*Animation* GetAnim(string animName, string maskColor) {
		if (!animContainer[animName]) {

			//Create and fill 
			deque<Image*> imgSequence;
			for (int i = 0; i < imagesAmount; i++) {

			}
		}
		return animContainer[animName];
	}*/

	//Used where's being setuped a new level
	void ClearContainer() {
		for (const auto& it : imgContainer) {
			delete it.second;
		}
		imgContainer.clear();

		for (const auto& it : animContainer) {
			delete it.second;
		}
		animContainer.clear();
	}

private:

	map<string, Image*> imgContainer;
	map<string, Animation*> animContainer;
	LuaS& lua = *(LuaS::Get());

	Image* CreateImage(string path) {
		int width, height;
		Image* newImg = new Image(CreateBitmap(path, &width, &height), &width, &height);
		//SetImageMask(newImg->image, ResolveMaskColor(maskColor));
		return newImg;
	}

	/*char* GetImagePath(string imageID) {
		lua.LoadStr("GetImagePath");
		lua.PushArgument<string>(imageID);
		lua.Exec(1, 1);
		return lua.GetArgument<char*>(-1);
	}*/

	/*Image* GetImage(string imgName, string path, string maskColor) {
		if (!imgContainer[imgName]) {
			int width;
			int height;
			Image* newImg = new Image(CreateImage(path, &width, &height), &width, &height);
			SetImageMask(newImg->image, ResolveMaskColor(maskColor));

			imgContainer[imgName] = newImg;
		}
		return imgContainer[imgName];
	}

	Animation* GetAnimation(string animName, string rootPath, string maskColor) {

	}*/

	/*static ALLEGRO_COLOR ResolveMaskColor(string maskText) {
		if (maskText == "White")
			return ACOLOR_WHITE;
		else if (maskText == "Black")
			return ACOLOR_BLACK;
		else if (maskText == "Yellow")
		return ACOLOR_YELLOW;
		else if (maskText == "Red")
			return ACOLOR_RED;
		else
			return ACOLOR_WHITE;
	}*/

};