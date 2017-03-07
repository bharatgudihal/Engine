#include "../MonsterController.h"

MonsterController::MonsterController(Engine::Pointer::WeakPointer<Engine::Actor> monster, Engine::Pointer::WeakPointer<Engine::Actor> player) :monsterReference(monster), playerReference(player) {}

void MonsterController::Update() {
	Engine::Math::Vector3 directionVector = playerReference.Acquire()->getPosition() - monsterReference.Acquire()->getPosition();
	directionVector.Normalize();
	monsterReference.Acquire()->setDirection(directionVector);
}