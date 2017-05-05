#pragma once
#include "Controllers\ActorController.h"

class DeathBoxController :public Engine::IActorController {
public:
	DeathBoxController(Engine::GameObject::GameObject* actorReference) :boxReference(actorReference) {}
	~DeathBoxController() {}
	void Update(float) override {}
	bool OnCollisionEnter(const Engine::Math::Vector3&, Engine::GameObject::GameObject*) override;
private:
	Engine::GameObject::GameObject* boxReference;
};