#pragma once
#include "../Actor/Actor.h"
#include "../Input/Input.h"

namespace Engine {
	namespace Physics {
		class PhysicsBody {
		public:
			PhysicsBody(Actor* i_actor, const float i_speed, const float i_mass = 1.0f, const float i_drag = 0.0f, const bool i_useGravity = false);
			void PhysicsUpdate(const float deltaTime);
			void ApplyForce();
		private:
			Actor* actor;
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