#pragma once
#include "Controllers\ActorController.h"

class BallController :public Engine::IActorController {
public:
	BallController(Engine::GameObject::GameObject*);
	~BallController() {}
	void Update(float) override;
	bool OnCollisionEnter(const Engine::Math::Vector3&, Engine::GameObject::GameObject*) override;
private:
	Engine::GameObject::GameObject* ballReference;
	float defaultForce;
	bool isFree = false;
	const float freeSpeedBoost = 5000.0f;
};