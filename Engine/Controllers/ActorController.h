#ifndef ACTORCONTROLLER_H
#define ACTORCONTROLLER_H


namespace Engine {
	namespace Math{
		class Vector3;
	}
	namespace GameObject {
		class GameObject;
	}
	class IActorController{
	public:		
		virtual void Update(float) = 0;
		virtual ~IActorController() {};
		// Return false if you want the Physics system to handle collision response
		virtual bool OnCollisionEnter(const Math::Vector3&, GameObject::GameObject* other) = 0;
	};
}
#endif // !ACTORCONTROLLER_H


