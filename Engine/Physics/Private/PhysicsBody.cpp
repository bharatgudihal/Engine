#include "../PhysicsBody.h"

namespace Engine {
	namespace Physics {
		PhysicsBody::PhysicsBody(Actor* i_actor, const float i_speed, const float i_mass, const float i_drag, const bool i_useGravity) {
			assert(i_mass);
			actor = i_actor;
			mass = i_mass;
			dragCoefficient = i_drag;
			useGravity = i_useGravity;
			speed = i_speed;
			currentVelocity = Vector2D::ZERO;
		}

		void PhysicsBody::ApplyForce() {
			if (Engine::Input::isDown) {
				switch (Engine::Input::keyCode)
				{
				case 65:
					force = Vector2D::LEFT;
					break;
				case 68:
					force = Vector2D::RIGHT;
					break;
				case 83:
					force = Vector2D::DOWN;
					break;
				case 87:
					force = Vector2D::UP;
					break;
				default:
					break;
				}
			}
			else {
				force = Vector2D::ZERO;
			}
		}

		Vector2D Physics::PhysicsBody::CalculateDrag() const{			
			Vector2D drag = currentVelocity*currentVelocity*dragCoefficient;
			if (currentVelocity.X() > 0) {
				drag.X(-drag.X());
			}
			else if(currentVelocity.X() < 0){
				drag.X(drag.X());
			}
			if (currentVelocity.Y() > 0) {
				drag.Y(-drag.Y());
			}
			else if (currentVelocity.Y() < 0) {
				drag.Y(drag.Y());
			}
			return drag;
		}

		void PhysicsBody::PhysicsUpdate(const float deltaTime) {
			Vector2D dragForce = CalculateDrag();
			Vector2D netForce = force * speed + dragForce + (useGravity ? GRAVITY : Vector2D::ZERO);
			Vector2D acceleration = netForce / mass;
			Vector2D previousVelocity = currentVelocity;
			currentVelocity = previousVelocity + acceleration * deltaTime;
			Vector2D newPosition = actor->getPosition() + ((previousVelocity + currentVelocity) / 2) * deltaTime;			
			actor->setPosition(newPosition);
		}
	}
}