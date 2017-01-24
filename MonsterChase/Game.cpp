#include "Game.h"

namespace Game {

	bool quit;
	GLib::Sprites::Sprite * player;
	void Update();

	void KeyChangeCallBack(unsigned int keyCode, bool isDown) {

	}

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

	void StartGame(HINSTANCE i_hInstance, int i_nCmdShow) {
		if (GLib::Initialize(i_hInstance, i_nCmdShow, "Game", -1, 800, 600)) {
			GLib::SetKeyStateChangeCallback(KeyChangeCallBack);
			size_t fileSize;
			void* file = LoadFile("Assets\\Sprites\\player.dds", fileSize);
			player = Engine::SpriteUtilities::CreateSprite(file, fileSize);
			assert(player);
			quit = false;
			do {
				GLib::Service(quit);
				Update();
			} while (!quit);
			if (player) {
				GLib::Sprites::Release(player);
			}
			GLib::Shutdown();
		}
	}

	void Update() {
		if (!quit) {
			GLib::BeginRendering();
			GLib::Sprites::BeginRendering();
			GLib::Point2D position = { 0,0 };
			GLib::Sprites::RenderSprite(*player, position, 0.0f);
			GLib::Sprites::EndRendering();
			GLib::EndRendering();
		}
	}
}