#include "../GLibTest.h"

void KeyCallback(unsigned int keyCode, bool isDown) {
	DEBUG_LOG("keyCode: %u\n", keyCode);
	DEBUG_LOG("isDown: %d\n", isDown);
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

GLib::Sprites::Sprite * CreateSprite(const char * fileName) {
	assert(fileName);
	size_t sizeOfFile = 0;
	void* file = LoadFile(fileName, sizeOfFile);
	GLib::Texture * texture = file ? GLib::CreateTexture(file, sizeOfFile) : nullptr;
	if (file) {
		delete[] file;
	}
	if (texture == nullptr) {
		return nullptr;
	}
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	bool result = GLib::GetDimensions(texture, width, height, depth);
	assert(result);
	assert((width > 0) && (height > 0));
	GLib::Sprites::SpriteEdges edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
	GLib::Sprites::SpriteUVs UVs = { { 0.0f, 0.0f },{ 1.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f } };
	GLib::RGBA Color = { 255, 255, 255, 255 };
	GLib::Sprites::Sprite * sprite = GLib::Sprites::CreateSprite(edges, 0.1f, Color, UVs);
	if (sprite == nullptr)
	{
		GLib::Release(texture);
		return nullptr;
	}
	GLib::Sprites::SetTexture(*sprite, *texture);

	return sprite;
}

void GLibTest(HINSTANCE i_hInstance, int i_nCmdShow) {
	bool success = GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
	if (success) {
		GLib::SetKeyStateChangeCallback(KeyCallback);
		GLib::Sprites::Sprite * player = CreateSprite("Assets\\Sprites\\player.dds");
		assert(player);
		GLib::Sprites::Sprite * enemy = CreateSprite("Assets\\Sprites\\enemy.dds");
		assert(enemy);
		bool quit = false;
		do {
			GLib::Service(quit);
			if (!quit) {
				GLib::BeginRendering();
				GLib::Sprites::BeginRendering();
				if (player) {
					static float moveDist = .01f;
					static float moveDir = moveDist;
					static GLib::Point2D Offset = { -180.0f,-100.0f };
					if (Offset.x < -220.0f) {
						moveDir = moveDist;
					}
					else if (Offset.x > -140.0f) {
						moveDir = -moveDist;
					}
					Offset.x += moveDir;
					GLib::Sprites::RenderSprite(*player, Offset, 0.0f);
				}
				if (enemy) {
					static float moveDist = .02f;
					static float moveDir = -moveDist;
					static GLib::Point2D Offset = { 180.0f, -100.0f };
					if (Offset.x > 200.0f) {
						moveDir = -moveDist;
					}
					else if (Offset.x < 160.0f) {
						moveDir = moveDist;
					}
					Offset.x += moveDir;
					GLib::Sprites::RenderSprite(*enemy, Offset, 0.0f);
				}
				GLib::Sprites::EndRendering();
				GLib::EndRendering();
			}
		} while (!quit);
		if (player)
			GLib::Sprites::Release(player);
		if (enemy)
			GLib::Sprites::Release(enemy);
		GLib::Shutdown();
	}
}