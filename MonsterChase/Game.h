#pragma once
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include "GLib.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderObject.h"
#include "Timer\CoreTimer.h"
#include "Actor\Actor.h"
#include "Input\Input.h"
#include "Physics\PhysicsBody.h"

namespace Game {
	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
}