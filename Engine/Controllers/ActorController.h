#ifndef ACTORCONTROLLER_H
#define ACTORCONTROLLER_H
namespace Engine {
	class Actor;

	class IActorController{
	public:
		inline virtual void SetActor(Actor* actor) = 0;
		virtual void Update(const char input) = 0;
		const float GRIDSIZE = 64;
	};
}
#endif // !ACTORCONTROLLER_H


