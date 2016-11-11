#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
using namespace Engine;
class MonsterController:public IActorController {
public:
	inline void SetActor(Engine::Actor* actor) override;
	void Update(const char input) override;
private:
	Engine::Actor* monster;
	inline Vector2D GetRandomDirection() const;
};
#include "MonsterController_Inl.h"
#endif // !MONSTERCONTROLLER_H
