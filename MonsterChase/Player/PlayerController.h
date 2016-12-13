#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Math\Vector2D.h"

class PlayerController:public Engine::IActorController {
	class Actor;
public:
	inline void SetActor(Engine::Actor* actor) override;
	void Update(const char input) override;
private:
	Engine::Actor* player;
	const Engine::Vector2D PLAYER_SPEED_X = Engine::Vector2D(1, 0);
	const Engine::Vector2D PLAYER_SPEED_Y = Engine::Vector2D(0, 1);
};
#include "PlayerController_Inl.h"
#endif // !PLAYERCONTROLLER_H

