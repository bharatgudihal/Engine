#pragma once
#include <stdint.h>
#include "Controllers\ActorController.h"

class HardBrickController :public Engine::IActorController {
public:
	HardBrickController(Engine::GameObject::GameObject*);
	~HardBrickController() {}
	void Update(float) override;
	bool OnCollisionEnter(const Engine::Math::Vector3&, Engine::GameObject::GameObject*) override;
private:
	Engine::GameObject::GameObject* brickReference;
	uint8_t hitCount;
	const uint8_t maxHitCount;
};