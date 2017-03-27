#include "../MonsterController.h"
#include "Timer\CoreTimer.h"

MonsterController::MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>* monster) :
	monsterReference(*monster) {}

void MonsterController::Update(float deltaTime) {
	Engine::Math::Vector3 rotation = monsterReference.Acquire()->GetRotation();
	rotation.Z(rotation.Z() + rotationSpeed * deltaTime);
	//monsterReference.Acquire()->SetRotation(rotation);	
	if (monsterReference.Acquire()->GetPosition().X() > 400.0f) {
		Engine::Math::Vector3 position = monsterReference.Acquire()->GetPosition();
		position.X(-400.0f);
		monsterReference.Acquire()->SetPosition(position);
	}
	if (monsterReference.Acquire()->GetPosition().X() < -400.0f) {
		Engine::Math::Vector3 position = monsterReference.Acquire()->GetPosition();
		position.X(400.0f);
		monsterReference.Acquire()->SetPosition(position);
	}
	if (monsterReference.Acquire()->GetPosition().Y() > 300.0f) {
		Engine::Math::Vector3 position = monsterReference.Acquire()->GetPosition();
		position.Y(-300.0f);
		monsterReference.Acquire()->SetPosition(position);
	}
	if (monsterReference.Acquire()->GetPosition().Y() < -300.0f) {
		Engine::Math::Vector3 position = monsterReference.Acquire()->GetPosition();
		position.Y(300.0f);
		monsterReference.Acquire()->SetPosition(position);
	}
}