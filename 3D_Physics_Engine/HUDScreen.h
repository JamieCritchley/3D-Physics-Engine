#pragma once

#include "Extras/Renderer.h"
#include <string>
#include <vector>


namespace VisualDebugger
{

	///A single HUD screen
	class HUDScreen
	{
		std::vector<std::string> content;

	public:
		int id;
		physx::PxReal font_size;
		physx::PxVec3 color;

		HUDScreen(int screen_id, const physx::PxVec3& _color = physx::PxVec3(1.f, 1.f, 1.f), const physx::PxReal& _font_size = 0.024f);

		///Add a single line of text
		void AddLine(std::string line);

		///Removes last line of text
		void RemoveLine();

		///Render the screen
		void Render();

		///Clear content of the screen
		void Clear();
	};
}

