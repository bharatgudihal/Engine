#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
#include "Pointer\WeakPointer.h"
#include "Input\Input.h"

class PlayerController:public Engine::IActorController {
public:
	PlayerController(Engine::Pointer::SmartPointer<Engine::Actor>*);
	~PlayerController(){}
	void Update() override;
private:
	Engine::Pointer::WeakPointer<Engine::Actor> playerReference;
};
#endif // !PLAYERCONTROLLER_H

