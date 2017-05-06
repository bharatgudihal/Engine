#include "Game.h"
#include "Profiling\ProfilerMacros.h"

namespace Game {

	void Game::GameObjectTask::ProcessFile(uint8_t* fileData, uint32_t fileSize) {
		Engine::LuaHelper::LuaHelper luaHelper(fileData, fileSize);
		luaHelper.LoadGlobalTable(Engine::String::ConstantStrings::GetInstance()->GAMEOBJECT.Get());
		float count = 1.0f;
		luaHelper.GetFloatFromTable(Engine::String::ConstantStrings::GetInstance()->COUNT.Get(), count, -1);
		Engine::String::PooledString controller = luaHelper.GetStringFromTable(Engine::String::ConstantStrings::GetInstance()->CONTROLLER.Get(), -1);
		Engine::String::PooledString isEnabled = luaHelper.GetStringFromTable(Engine::String::ConstantStrings::GetInstance()->ISENABLED.Get(), -1);
		static const Engine::String::PooledString PLAYERCONTROLLER("PlayerController");
		static const Engine::String::PooledString BRICKCONTROLLER("BrickController");
		static const Engine::String::PooledString BALLCONTROLLER("BallController");
		static const Engine::String::PooledString DEATHBOXCONTROLLER("DeathBoxController");
		static const Engine::String::PooledString HARDBRICKCONTROLLER("HardBrickController");
		luaHelper.Pop();
		for (int i = 0; i < count; i++) {
			Engine::GameObject::GameObject* gameObject = Engine::GameObject::GameObject::Create(&luaHelper);
			assert(gameObject);
			if (controller == PLAYERCONTROLLER) {
				gameObject->SetController(new PlayerController(gameObject->GetActorReference()));
			}
			else if (controller == BRICKCONTROLLER || controller == HARDBRICKCONTROLLER) {
				if (controller == BRICKCONTROLLER) {
					gameObject->SetController(new BrickController(gameObject));
				}else{
					gameObject->SetController(new HardBrickController(gameObject));
				}
				Engine::Math::Vector3& originalPosition = (*gameObject->GetActorReference())->GetPosition();
				originalPosition.X(originalPosition.X() + i*(*gameObject->GetActorReference())->GetBounds().Extents.X() * 2);
				(*gameObject->GetActorReference())->SetPosition(originalPosition);
			}
			else if (controller == BALLCONTROLLER) {
				gameObject->SetController(new BallController(gameObject));
			}
			else if (controller == DEATHBOXCONTROLLER) {
				gameObject->SetController(new DeathBoxController(gameObject));
			}
			if (isEnabled == Engine::String::ConstantStrings::GetInstance()->FALSE_STRING) {
				gameObject->SetEnabled(false);
			}
			UpdatePostProcessQueue(gameObject);
		}
	}

	void Game::InitializeActors() {
		GameObjectTask* task1 = new GameObjectTask("Assets\\Data\\WallLeft.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task1);
		GameObjectTask* task2 = new GameObjectTask("Assets\\Data\\WallRight.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task2);
		GameObjectTask* task3 = new GameObjectTask("Assets\\Data\\WallTop.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task3);
		GameObjectTask* task4 = new GameObjectTask("Assets\\Data\\WallBottom.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task4);
		GameObjectTask* task5 = new GameObjectTask("Assets\\Data\\Row1.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task5);
		GameObjectTask* task6 = new GameObjectTask("Assets\\Data\\Row2.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task6);
		GameObjectTask* task7 = new GameObjectTask("Assets\\Data\\Row3.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task7);
		GameObjectTask* task8 = new GameObjectTask("Assets\\Data\\Row4.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task8);
		GameObjectTask* task9 = new GameObjectTask("Assets\\Data\\Player.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task9);
		GameObjectTask* task10 = new GameObjectTask("Assets\\Data\\Ball.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task10);
		GameObjectTask* task11 = new GameObjectTask("Assets\\Data\\You_Lost.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task11);
		GameObjectTask* task12 = new GameObjectTask("Assets\\Data\\You_Won.lua", &pendingGameObjectsQueue, &pendingQueueMutex);
		Engine::Utility::FileProcessor::GetInstance().InsertInLoadQueue(*task12);
	}

	void Game::TearDownActors() {
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
			delete sceneObjects[i];
		}
	}

	void Game::StartGame(HINSTANCE i_hInstance, int i_nCmdShow) {
		Engine::Messaging::MessagingSystem::GetInstance()->RegisterMessageHandler("BrickDestroyed", this);
		Engine::Messaging::MessagingSystem::GetInstance()->RegisterMessageHandler("GameLost", this);
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
		Engine::Messaging::MessagingSystem::GetInstance()->DeRegisterMessageHandler("GameLost", this);
		Engine::Messaging::MessagingSystem::GetInstance()->DeRegisterMessageHandler("BrickDestroyed", this);
	}

	void Game::HandleMessage(const Engine::String::HashedString& message) {
		if (message == "ActorAdded") {
			CheckForNewGameObjects();
		}
		if (message == "BrickDestroyed") {
			ReduceBrickCount();
		}
		if (message == "GameLost") {
			GameLost();
		}
	}

	void Game::CheckForNewGameObjects() {
		Engine::GameObject::GameObject* gameObject = nullptr;
		pendingQueueMutex.Acquire();
		while (!pendingGameObjectsQueue.empty()) {
			gameObject = static_cast<Engine::GameObject::GameObject*>(pendingGameObjectsQueue.front());
			if ((*gameObject->GetActorReference())->GetNameHash() == "WinScreen") {
				winScreen = gameObject;
			}
			if ((*gameObject->GetActorReference())->GetNameHash() == "LoseScreen") {
				loseScreen = gameObject;
			}
			pendingGameObjectsQueue.pop();
			if (gameObject != nullptr) {
				sceneObjects.push_back(gameObject);
			}
		}
		pendingQueueMutex.Release();		
	}

	void Game::ReduceBrickCount()
	{
		if (--bricksLeft == 0) {
			DEBUG_LOG("WINNER!\n");
			pause = true;
			winScreen->SetEnabled(true);
		}
	}

	void Game::GameLost()
	{
		pause = true;
		loseScreen->SetEnabled(true);
	}

	void Game::Update() {
		if (!quit) {
			if (!pause) {
				Engine::Controller::UpdateAll(sceneObjects, deltaTime);
				PROFILE_SCOPE_BEGIN("Collision");
				Engine::Physics::Collision::Update(sceneObjects, deltaTime);
				PROFILE_SCOPE_END();
				Engine::Physics::UpdateAll(sceneObjects, deltaTime);
			}
			Engine::Renderer::DrawAll(sceneObjects);
			CheckForNewGameObjects();
		}
	}
}