#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
#include "Pointer\WeakPointer.h"

class MonsterController :public Engine::IActorController{
public:
	MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>*);
	void Update(float) override;
private:
	Engine::Pointer::WeakPointer<Engine::Actor> monsterReference;
	float rotationSpeed = 80.0f;
};
#endif // !MONSTERCONTROLLER_H
