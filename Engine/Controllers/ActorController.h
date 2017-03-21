#ifndef ACTORCONTROLLER_H
#define ACTORCONTROLLER_H


namespace Engine {
	class IActorController{
	public:		
		virtual void Update() = 0;
		virtual ~IActorController() {};
	};
}
#endif // !ACTORCONTROLLER_H


