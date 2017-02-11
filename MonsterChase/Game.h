#pragma once
#include <Windows.h>
#include "GLib.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderObject.h"
#include "Timer\CoreTimer.h"
#include "Actor\Actor.h"
#include "Input\Input.h"
#include "Physics\PhysicsBody.h"
#include "Utility\Utility.h"
#include "GameObject\GameObject.h"
namespace Game {
	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
}