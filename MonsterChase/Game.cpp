#include "Game.h"

namespace Game {

	void Game::GameObjectTask::ProcessFile(uint8_t* fileData, uint32_t fileSize) {
		Engine::LuaHelper::LuaHelper luaHelper(fileData, fileSize);
		luaHelper.LoadGlobalTable(Engine::String::ConstantStrings::GetInstance()->GAMEOBJECT.Get());
		float count = 1.0f;
		luaHelper.GetFloatFromTable(Engine::String::ConstantStrings::GetInstance()->COUNT.Get(), count, -1);
		Engine::String::PooledString controller = luaHelper.GetStringFromTable(Engine::String::ConstantStrings::GetInstance()->CONTROLLER.Get(), -1);
		luaHelper.Pop();
		srand(static_cast<unsigned int>(time(NULL)));
		for (int i = 0; i < count; i++) {
			Engine::GameObject::GameObject* player = Engine::GameObject::GameObject::Create(&luaHelper);			
			if (controller == Engine::String::ConstantStrings::GetInstance()->PLAYERCONTROLLER) {
				player->SetController(new PlayerController(player->GetActorReference()));
				Engine::Math::Vector3 rotation(0.0f, 0.0f, static_cast<float>(rand() % 360));
			}
			else if (controller == Engine::String::ConstantStrings::GetInstance()->MONSTERCONTROLLER) {
				player->SetController(new MonsterController(player->GetActorReference()));
				Engine::Math::Vector3 forward(static_cast<float>(-50.0f + rand() % 100), static_cast<float>(-50.0f + rand() % 100));
				forward.Normalize();
				(*(player->GetActorReference()))->SetForward(forward);
				Engine::Math::Vector3 extents = (*(player->GetActorReference()))->GetBounds().Extents;
				Engine::Math::Vector3 position((-400.0f + extents.X() + static_cast<float>(rand() % 800 - extents.X())), (-300.0f + extents.Y() + static_cast<float>(rand() % 600 - extents.Y())));
				(*(player->GetActorReference()))->SetPosition(position);
				Engine::Math::Vector3 rotation(0.0f, 0.0f, static_cast<float>(rand() % 360));
				if (rand() % 2) {
					//(*(player->GetActorReference()))->SetRotation(rotation);
				}
			}
			assert(player);
			UpdatePostProcessQueue(player);
		}
	}

	void Game::InitializeActors() {
		//GameObjectTask* task1 = new GameObjectTask("Assets\\Data\\Player.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		//Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task1);
		GameObjectTask* task1 = new GameObjectTask("Assets\\Data\\WallLeft.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task1);
		GameObjectTask* task2 = new GameObjectTask("Assets\\Data\\WallRight.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task2);
		GameObjectTask* task3 = new GameObjectTask("Assets\\Data\\WallTop.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task3);
		GameObjectTask* task4 = new GameObjectTask("Assets\\Data\\WallBottom.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task4);
		GameObjectTask* task5 = new GameObjectTask("Assets\\Data\\Monster.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task5);
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
			Engine::Controller::UpdateAll(sceneObjects, deltaTime);
			if (Engine::Input::keyCode == 81 && Engine::Input::isDown) {
				int a = 0;
			}
			Engine::Physics::Collision::Update(sceneObjects, deltaTime);
			Engine::Physics::UpdateAll(sceneObjects, deltaTime);
			Engine::Renderer::DrawAll(sceneObjects);
		}
	}
}