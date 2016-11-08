#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
using namespace Engine;
class PlayerController:public IActorController {
public:
	inline void SetActor(Actor* actor) override;
	void Update(const char input) override;
private:
	Actor* player;
	const Engine::Vector2D PLAYER_SPEED_X = Engine::Vector2D(1, 0);
	const Engine::Vector2D PLAYER_SPEED_Y = Engine::Vector2D(0, 1);
};
#include "PlayerController_Inl.h"
#endif // !PLAYERCONTROLLER_H

