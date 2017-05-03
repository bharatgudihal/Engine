#pragma once
#include "Controllers\ActorController.h"

class BrickController :public Engine::IActorController {
public:
	BrickController(Engine::GameObject::GameObject*);
	~BrickController() {}
	void Update(float) override;
	bool OnCollisionEnter(const Engine::Math::Vector3&, Engine::GameObject::GameObject*) override;
private:
	Engine::GameObject::GameObject* brickReference;
	bool isDisabled = false;
};