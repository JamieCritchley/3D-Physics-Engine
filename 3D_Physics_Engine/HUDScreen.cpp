#include "HUDScreen.h"

namespace VisualDebugger
{
	HUDScreen::HUDScreen(int screen_id, const physx::PxVec3& _color, const physx::PxReal& _font_size) :
		id(screen_id), color(_color), font_size(_font_size) {}

	void HUDScreen::AddLine(std::string line)
	{
		content.push_back(line);
	}

	void HUDScreen::RemoveLine()
	{
		content.pop_back();

	}

	void HUDScreen::Render()
	{
		for (unsigned int i = 0; i < content.size(); i++)
			Renderer::RenderText(content[i], physx::PxVec2(0.0, 1.f - (i + 1) * font_size), color, font_size);
	}

	void HUDScreen::Clear()
	{
		content.clear();
	}
}