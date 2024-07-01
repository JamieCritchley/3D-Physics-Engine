#pragma once

#include "Renderer.h"
#include <string>
#include <list>
#include "HUDScreen.h"

namespace VisualDebugger
{
	using namespace std;



	///HUD class containing multiple screens
	class HUD
	{
		int active_screen;
		vector<HUDScreen*> screens;

	public:
		~HUD();

		///Add a single line to a specific screen
		void AddLine(int screen_id, string line);

		//Removes a specific line from the screen
		void RemoveLine(int screen_id);

		///Set the active screen
		void ActiveScreen(int value);

		///Get the active screen
		int ActiveScreen();

		///Clear a specified screen (or all of them)
		void Clear(int screen_id = -1);

		///Change the font size for a specified screen (-1 = all)
		void FontSize(physx::PxReal font_size, unsigned int screen_id = -1);

		///Change the color for a specified screen (-1 = all)
		void Color(physx::PxVec3 color, unsigned int screen_id = -1);

		///Render the active screen
		void Render();
	};
}

