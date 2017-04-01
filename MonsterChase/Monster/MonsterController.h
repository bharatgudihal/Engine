#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include <math.h>
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
#include "Pointer\WeakPointer.h"
#include "Math\Matrix.h"

class MonsterController :public Engine::IActorController{
public:
	MonsterController(Engine::Pointer::SmartPointer<Engine::Actor>*);
	void Update(float) override;
private:
	Engine::Pointer::WeakPointer<Engine::Actor> monsterReference;
};
#endif // !MONSTERCONTROLLER_H
