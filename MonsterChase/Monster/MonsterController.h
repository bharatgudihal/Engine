#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Actor\Actor.h"
using namespace Engine;
class MonsterController:public IActorController {
public:
	inline void SetActor(Actor* actor) override;
	void Update(const char input) override;
private:
	Actor* monster;
	inline Vector2D GetRandomVector();
};
#include "MonsterController_Inl.h"
#endif // !MONSTERCONTROLLER_H
