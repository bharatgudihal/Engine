#include "Game.h"

namespace Game {

	void Game::InitializeActors() {
		Engine::LuaHelper::LuaHelper luaHelper("Assets\\Data\\Player.lua");
		Engine::GameObject::GameObject* player = Engine::GameObject::GameObject::Create(&luaHelper);
		luaHelper.LoadGlobalTable(Engine::String::ConstantStrings::GetInstance()->PLAYER.Get());
		Engine::String::PooledString controller = luaHelper.GetStringFromTable(Engine::String::ConstantStrings::GetInstance()->CONTROLLER.Get(), -1);
		luaHelper.Pop();
		if (controller == Engine::String::ConstantStrings::GetInstance()->PLAYERCONTROLLER) {
			player->SetController(new PlayerController(player->GetActorReference()));
		}
		assert(player);
		sceneObjects.push_back(player);
	}

	void Game::TearDownActors() {
		for (int i = 0; i < sceneObjects.size(); i++) {
			delete sceneObjects[i];
		}
	}

	void Game::StartGame(HINSTANCE i_hInstance, int i_nCmdShow) {
		if (GLib::Initialize(i_hInstance, i_nCmdShow, "Game", -1, 800, 600)) {
			GLib::SetKeyStateChangeCallback(Engine::Input::KeyChangeCallBack);
			InitializeActors();
			quit = false;
			do {
				deltaTime = Engine::CoreTimer::GetDeltaTime();
				GLib::Service(quit);
				Update();
			} while (!quit);
			TearDownActors();
			GLib::Shutdown();
		}
	}

	void Game::Update() {
		if (!quit) {
			for (int i = 0; i < sceneObjects.size(); i++) {
				sceneObjects[i]->Update(deltaTime);
			}
		}
	}
}