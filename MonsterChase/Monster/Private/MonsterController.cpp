#include "../MonsterController.h"
#include "Timer\CoreTimer.h"

MonsterController::MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>* monster) :
	monsterReference(*monster) {}

void MonsterController::Update(float deltaTime) {
	Engine::Math::Vector3 rotation = monsterReference.Acquire()->GetRotation();
	rotation.Z(rotation.Z() + rotationSpeed * deltaTime);
	//monsterReference.Acquire()->SetRotation(rotation);
	if (monsterReference.Acquire()->GetPosition().X() + monsterReference.Acquire()->GetBounds().Extents.X() > 400.0f) {
		Engine::Math::Vector3 forward = monsterReference.Acquire()->GetForward();
		if (forward.X() > 0.0f) {
			forward.X(-forward.X());
		}
		monsterReference.Acquire()->SetForward(forward);
	}
	if (monsterReference.Acquire()->GetPosition().X() - monsterReference.Acquire()->GetBounds().Extents.X() < -400.0f) {
		Engine::Math::Vector3 forward = monsterReference.Acquire()->GetForward();
		if (forward.X() < 0.0f) {
			forward.X(-forward.X());
		}
		monsterReference.Acquire()->SetForward(forward);
	}
	if (monsterReference.Acquire()->GetPosition().Y() + 2*monsterReference.Acquire()->GetBounds().Extents.Y() > 300.0f) {
		Engine::Math::Vector3 forward = monsterReference.Acquire()->GetForward();
		if (forward.Y() > 0.0f) {
			forward.Y(-forward.Y());
		}
		monsterReference.Acquire()->SetForward(forward);
	}
	if (monsterReference.Acquire()->GetPosition().Y() < -300.0f) {
		Engine::Math::Vector3 forward = monsterReference.Acquire()->GetForward();
		if (forward.Y() < 0.0f) {
			forward.Y(-forward.Y());
		}
		monsterReference.Acquire()->SetForward(forward);
	}
}