#include "../MonsterController.h"
#include "Timer\CoreTimer.h"

MonsterController::MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>* monster) :
	monsterReference(*monster) {}

void MonsterController::Update(float deltaTime) {
	Engine::Math::Vector3 rotation = monsterReference.Acquire()->getRotation();
	rotation.Z(rotation.Z() + rotationSpeed * deltaTime);
	monsterReference.Acquire()->setRotation(rotation);
	monsterReference.Acquire()->setDirection(Engine::Math::Vector3::RIGHT);
	if (monsterReference.Acquire()->getPosition().X() > 400.0f) {
		Engine::Math::Vector3 position = monsterReference.Acquire()->getPosition();
		position.X(-400.0f);
		monsterReference.Acquire()->setPosition(position);
	}
}