#include "../PhysicsBody.h"

namespace Engine {
	namespace Physics {
		PhysicsBody::PhysicsBody(Pointer::SmartPointer<Actor> smartPointer, const float i_speed, const float i_mass, const float i_drag, const bool i_useGravity):weakPointer(smartPointer){
			assert(i_mass);
			mass = i_mass;
			dragCoefficient = i_drag;
			useGravity = i_useGravity;
			speed = i_speed;
			currentVelocity = Vector::ZERO;
		}

		Vector Physics::PhysicsBody::CalculateDrag() const{			
			Vector drag = currentVelocity*currentVelocity*dragCoefficient;
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
			Vector dragForce = CalculateDrag();
			Engine::Pointer::SmartPointer<Actor> smartPtr = weakPointer.Acquire();
			Vector netForce = smartPtr->getDirection() * speed + dragForce + (useGravity ? GRAVITY : Vector::ZERO);
			Vector acceleration = netForce / mass;
			Vector previousVelocity = currentVelocity;
			currentVelocity = previousVelocity + acceleration * deltaTime;			
			Vector newPosition = smartPtr->getPosition() + ((previousVelocity + currentVelocity) / 2) * deltaTime;
			smartPtr->setPosition(newPosition);
		}
	}
}