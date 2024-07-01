#pragma once

#include "MyPhysicsEngine.h"

namespace VisualDebugger
{
	using namespace physx;

	//Moved toheader file to allow scene to have access
	enum HUDState
	{
		EMPTY = 0,
		HELP = 1,
		PAUSE = 2
	};


	///Init visualisation
	void Init(const char *window_name, int width=512, int height=512);

	///Start visualisation
	void Start();

	void RenderScene(int t);
}

