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
		private:
			Pointer::WeakPointer<Actor> weakPointer;
			float mass;
			float dragCoefficient;
			float speed;
			Vector currentVelocity;
			bool useGravity;
			const Vector GRAVITY = Vector(0.0f, -9.8f);
			Vector force;
			Vector CalculateDrag() const;
		};		
	}
}