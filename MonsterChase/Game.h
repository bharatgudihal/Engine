#pragma once
#include <Windows.h>
#include <vector>
#include <time.h>
#include "GLib.h"
#include "Renderer\Renderer.h"
#include "Timer\CoreTimer.h"
#include "Input\Input.h"
#include "Utility\Utility.h"
#include "GameObject\GameObject.h"
#include "Lua\LuaHelper.h"
#include "Controllers\Controller.h"
#include "Physics\CollisionCheck.h"
#include "Physics\Physics.h"
#include "Player\PlayerController.h"
#include "Brick\BrickController.h"
#include "Brick\HardBrickController.h"
#include "Ball\BallController.h"
#include "DeathBox\DeathBoxController.h"
#include "Messaging\MessagingSystem.h"
#include "String\PooledString.h"

namespace Game {
	class Game:public Engine::Messaging::IMessageHandler {
	public:
		class GameObjectTask :public Engine::Utility::FileProcessor::Task {
		public:
			GameObjectTask(const char* fileName, std::queue<void*>* i_postProcessQueue, Engine::Threading::Mutex* i_postProcessMutex) :Engine::Utility::FileProcessor::Task(fileName, i_postProcessQueue, i_postProcessMutex) {};
			void ProcessFile(uint8_t*, uint32_t) override;
		};
		void StartGame(HINSTANCE i_hInstance, int i_nCmdShow);
		void HandleMessage(const Engine::String::HashedString&) override;
	private:		
		std::vector<Engine::GameObject::GameObject*> sceneObjects;
		std::queue<void*> pendingGameObjectsQueue;
		Engine::Threading::Mutex pendingQueueMutex;
		Engine::Threading::Mutex sceneQueueMutex;
		Engine::GameObject::GameObject* winScreen;
		Engine::GameObject::GameObject* loseScreen;
		float deltaTime;
		int bricksLeft = 32;
		bool pause;
		bool quit;
		void Update();
		void InitializeActors();
		void TearDownActors();
		void CheckForNewGameObjects();
		void ReduceBrickCount();
		void GameLost();
	};	
}