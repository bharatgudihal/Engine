#pragma once
#include <Windows.h>
#include <vector>
#include "GLib.h"
#include "Renderer\Renderer.h"
#include "Renderer\RenderObject.h"
#include "Timer\CoreTimer.h"
#include "Input\Input.h"
#include "Physics\PhysicsBody.h"
#include "Utility\Utility.h"
#include "GameObject\GameObject.h"
#include "Lua\LuaHelper.h"
#include "Player\PlayerController.h"
#include "Monster\MonsterController.h"
namespace Game {
	class Game {
	public:
		void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
	private:
		bool quit;
		std::vector<Engine::GameObject::GameObject*> sceneObjects;
		float deltaTime;
		void Update();
		void InitializeActors();
		void TearDownActors();
	};	
}