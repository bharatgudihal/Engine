#pragma once
#include "../Actor/Actor.h"
#include "../Input/Input.h"

namespace Engine {
	namespace Physics {
		class PhysicsBody {
		public:
			PhysicsBody(Actor* i_actor, float i_speed, float i_mass = 1.0f, float i_drag = 0.0f, bool i_useGravity = false);
			void PhysicsUpdate(float deltaTime);
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
			Vector2D CalculateDrag();
		};		
	}
}