#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H
#include "Controllers\ActorController.h"
#include "Math\Vector2D.h"

class MonsterController :public Engine::IActorController{
	class Actor;
public:
	inline void SetActor(Engine::Actor* actor) override;
	void Update(const char input) override;
private:
	Engine::Actor* monster;
	inline Engine::Vector2D GetRandomDirection() const;
};
#include "MonsterController_Inl.h"
#endif // !MONSTERCONTROLLER_H
