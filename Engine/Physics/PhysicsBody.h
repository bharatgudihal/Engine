#pragma once
#include "../Actor/Actor.h"
#include "../Input/Input.h"
#include "../Pointer/WeakPointer.h"

namespace Engine {
	namespace Physics {
		class PhysicsBody {
		public:
			PhysicsBody(Pointer::SmartPointer<Actor> smartPointer, const float i_speed, const float i_mass = 1.0f, const float i_drag = 0.0f, const bool i_useGravity = false);
			~PhysicsBody() {};
			void PhysicsUpdate(const float deltaTime);
			Math::Vector3 GetVelocity();
			void SetVelocity(Math::Vector3&);
			float GetSpeed() { return speed; }
			void SetSpeed(const float newSpeed) { speed = newSpeed; }
		private:
			Pointer::WeakPointer<Actor> weakPointer;
			float mass;
			float dragCoefficient;
			float speed;
			Math::Vector3 currentVelocity;
			bool useGravity;
			const Math::Vector3 GRAVITY = Math::Vector3(0.0f, -9.8f);
			Math::Vector3 force;
			Math::Vector3 CalculateDrag() const;
		};		
	}
}