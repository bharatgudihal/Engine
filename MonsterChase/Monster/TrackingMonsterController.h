#ifndef TRACKING_MONSTERCONTROLLER_H
#define TRACKING_MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
using namespace Engine;
class TrackingMonsterController :public IActorController {
public:
	inline void SetActor(Engine::Actor* actor) override;
	inline void Update(const char input) override;
	void SetDirection(const Engine::Actor* player);
private:
	Engine::Actor* monster;
	float speed = 5;
};
#include "TrackingMonsterController_Inl.h"
#endif // !TRACKING_MONSTERCONTROLLER_H
