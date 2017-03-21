#include "Game.h"

namespace Game {

	void Game::GameObjectTask::ProcessFile(uint8_t* fileData, uint32_t fileSize) {
		Engine::LuaHelper::LuaHelper luaHelper(fileData, fileSize);
		Engine::GameObject::GameObject* player = Engine::GameObject::GameObject::Create(&luaHelper);
		luaHelper.LoadGlobalTable(Engine::String::ConstantStrings::GetInstance()->GAMEOBJECT.Get());
		Engine::String::PooledString controller = luaHelper.GetStringFromTable(Engine::String::ConstantStrings::GetInstance()->CONTROLLER.Get(), -1);
		luaHelper.Pop();
		if (controller == Engine::String::ConstantStrings::GetInstance()->PLAYERCONTROLLER) {
			player->SetController(new PlayerController(player->GetActorReference()));
		}
		else if (controller == Engine::String::ConstantStrings::GetInstance()->MONSTERCONTROLLER) {
			player->SetController(new MonsterController(player->GetActorReference()));
		}
		assert(player);
		UpdatePostProcessQueue(player);
	}

	void Game::InitializeActors() {
		GameObjectTask* task1 = new GameObjectTask("Assets\\Data\\Player.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task1);
		GameObjectTask* task2 = new GameObjectTask("Assets\\Data\\Monster.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task2);
	}

	void Game::TearDownActors() {
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
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
				CheckForNewGameObjects();
			} while (!quit);
			TearDownActors();
			GLib::Shutdown();
		}
	}

	void Game::CheckForNewGameObjects() {
		void* gameObject = nullptr;
		pendingQueueMutex.Acquire();
		if (!pendingGameObjectsQueue.empty()) {
			gameObject = pendingGameObjectsQueue.front();
			pendingGameObjectsQueue.pop();
		}
		pendingQueueMutex.Release();
		if (gameObject != nullptr) {
			sceneObjects.push_back(static_cast<Engine::GameObject::GameObject*>(gameObject));
		}
	}

	void Game::Update() {
		if (!quit) {
			/*GLib::BeginRendering();
			GLib::Sprites::BeginRendering();
			for (unsigned int i = 0; i < sceneObjects.size(); i++) {
				sceneObjects[i]->Update(deltaTime);
			}
			GLib::Sprites::EndRendering();
			GLib::EndRendering();*/
			Engine::Controller::UpdateAll(sceneObjects);
			Engine::Physics::Collision::CheckCollisions(sceneObjects);
			Engine::Physics::UpdateAll(sceneObjects, deltaTime);
			Engine::Renderer::DrawAll(sceneObjects);
		}
	}
}