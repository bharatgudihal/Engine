#pragma once
#include "../Actor/Actor.h"
#include "../Input/Input.h"
#include "../Pointer/WeakPointer.h"

namespace Engine {
	namespace Physics {
		class PhysicsBody {
		public:
			PhysicsBody(Pointer::SmartPointer<Actor> smartPointer, const float i_speed, const float i_mass = 1.0f, const float i_drag = 0.0f, const bool i_useGravity = false);
			void PhysicsUpdate(const float deltaTime);
			void ApplyForce();
		private:
			Pointer::WeakPointer<Actor> weakPointer;
			float mass;
			float dragCoefficient;
			float speed;
			Vector2D currentVelocity;
			bool useGravity;
			const Vector2D GRAVITY = Vector2D(0.0f, -9.8f);
			Vector2D force;
			Vector2D CalculateDrag() const;
		};		
	}
}