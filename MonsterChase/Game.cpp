#include "Game.h"

namespace Game {

	bool quit;
	GLib::Sprites::Sprite * playerSprite;
	Engine::Actor playerActor;
	float deltaTime;
	void Update();
	Engine::Physics::PhysicsBody* physicsBody;

	void* LoadFile(const char* fileName, size_t & size) {
		FILE * file = nullptr;
		errno_t error = fopen_s(&file, fileName, "rb");
		if (error != 0) {
			return nullptr;
		}
		assert(file != nullptr);
		int fileIOError = fseek(file, 0, SEEK_END);
		assert(fileIOError == 0);
		long fileSize = ftell(file);
		assert(fileSize >= 0);
		fileIOError = fseek(file, 0, SEEK_SET);
		assert(fileIOError == 0);
		uint8_t * buffer = new uint8_t[fileSize];
		assert(buffer);
		size_t FileRead = fread(buffer, 1, fileSize, file);
		assert(FileRead == fileSize);
		fclose(file);
		size = fileSize;
		return buffer;
	}

	void InitializeActors() {
		size_t fileSize;
		void* file = LoadFile("Assets\\Sprites\\player.dds", fileSize);
		playerSprite = Engine::Renderer::CreateSprite(file, fileSize);
		delete file;
		playerActor.setPosition(Engine::Vector2D::ZERO);
		physicsBody = new Engine::Physics::PhysicsBody(&playerActor,100.0f,1.0f,0.05f);
		assert(playerSprite);
	}

	void TearDownActors() {
		delete physicsBody;
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
			if (playerSprite) {
				GLib::Sprites::Release(playerSprite);
			}
			TearDownActors();
			GLib::Shutdown();
		}
	}

	void Update() {
		if (!quit) {
			physicsBody->ApplyForce();
			physicsBody->PhysicsUpdate(deltaTime);
			Engine::Renderer::Draw(&playerActor, playerSprite);			
		}
	}
}