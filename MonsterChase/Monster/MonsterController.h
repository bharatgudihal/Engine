#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
#include "Pointer\WeakPointer.h"

class MonsterController :public Engine::IActorController{
public:
	MonsterController(Engine::Pointer::WeakPointer<Engine::Actor>, Engine::Pointer::WeakPointer<Engine::Actor>);
	void Update() override;
private:
	Engine::Pointer::WeakPointer<Engine::Actor> monsterReference;
	Engine::Pointer::WeakPointer<Engine::Actor> playerReference;
};
#endif // !MONSTERCONTROLLER_H
