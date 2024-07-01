#include "Extras/HUD.h"

namespace VisualDebugger
{
	HUD::~HUD()
	{
		for (unsigned int i = 0; i < screens.size(); i++)
			delete screens[i];
	}


	void HUD::AddLine(int screen_id, string line)
	{
		for (unsigned int i = 0; i < screens.size(); i++)
		{
			if (screens[i]->id == screen_id)
			{
				screens[i]->AddLine(line);
				return;
			}
		}

		screens.push_back(new HUDScreen(screen_id));
		screens.back()->AddLine(line);
	}

	void HUD::RemoveLine(int screen_id)
	{
		for (unsigned int i = 0; i < screens.size(); i++)
		{
			if (screens[i]->id == screen_id)
			{
				screens[i]->RemoveLine();
				return;
			}
		}

		screens.push_back(new HUDScreen(screen_id));
		screens.back()->RemoveLine();
	}

	void HUD::ActiveScreen(int value)
	{
		active_screen = value;
	}

	void HUD::Clear(int screen_id)
	{
		if (screen_id == -1)
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				screens[i]->Clear();
			}
		}
		else
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				if (screens[i]->id == screen_id)
				{
					screens[i]->Clear();
					return;
				}
			}
		}
	}

	void HUD::FontSize(physx::PxReal font_size, unsigned int screen_id)
	{
		if (screen_id == -1)
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				screens[i]->font_size = font_size;
			}
		}
		else
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				if (screens[i]->id == screen_id)
				{
					screens[i]->font_size = font_size;
					return;
				}
			}
		}
	}

	void HUD::Color(physx::PxVec3 color, unsigned int screen_id)
	{
		if (screen_id == -1)
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				screens[i]->color = color;
			}
		}
		else
		{
			for (unsigned int i = 0; i < screens.size(); i++)
			{
				if (screens[i]->id == screen_id)
				{
					screens[i]->color = color;
					return;
				}
			}
		}
	}

	void HUD::Render()
	{
		for (unsigned int i = 0; i < screens.size(); i++)
		{
			if (screens[i]->id == active_screen)
			{
				screens[i]->Render();
				return;
			}
		}
	}

}