#include "../MonsterController.h"
#include "Timer\CoreTimer.h"

MonsterController::MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>* monster) :
	monsterReference(*monster) {}

void MonsterController::Update() {
	Engine::Math::Vector3 rotation = monsterReference.Acquire()->getRotation();
	rotation.Z(rotation.Z() + rotationSpeed * Engine::CoreTimer::GetDeltaTime());
	monsterReference.Acquire()->setRotation(rotation);
}