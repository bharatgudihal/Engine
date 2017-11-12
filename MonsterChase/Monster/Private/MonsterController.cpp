#include "../MonsterController.h"
#include "Timer\CoreTimer.h"

MonsterController::MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>* monster) :
	monsterReference(*monster) {}

void MonsterController::Update(float deltaTime) {
	Engine::Math::Vector3 Extents = monsterReference.Acquire()->GetBounds().Extents;
	Engine::Math::Vector3 position((-400.0f + Extents.X() + static_cast<float>(rand() % 800 - Extents.X())), (-300.0f + Extents.Y() + static_cast<float>(rand() % 600 - Extents.Y())));
	if (fabs(monsterReference.Acquire()->GetPosition().X()) > 400.0f) {
		monsterReference.Acquire()->SetPosition(position);
	}
	if (fabs(monsterReference.Acquire()->GetPosition().Y()) > 300.0f) {
		monsterReference.Acquire()->SetPosition(position);
	}
}