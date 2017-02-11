#include "Game.h"

namespace Game {

	bool quit;
	Engine::GameObject::GameObject* player;
	float deltaTime;
	void Update();

	void InitializeActors() {
		player = Engine::GameObject::GameObject::Create("Assets\\Data\\Player.lua");
		assert(player);
	}

	void TearDownActors() {
		delete player;
	}

	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow) {
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

	void Update() {
		if (!quit) {
			player->Update(deltaTime);
		}
	}
}