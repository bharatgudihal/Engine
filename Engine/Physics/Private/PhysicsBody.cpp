#include "../PhysicsBody.h"

namespace Engine {
	namespace Physics {
		PhysicsBody::PhysicsBody(Pointer::SmartPointer<Actor> smartPointer, const float i_speed, const float i_mass, const float i_drag, const bool i_useGravity):weakPointer(smartPointer){
			assert(i_mass);
			mass = i_mass;
			dragCoefficient = i_drag;
			useGravity = i_useGravity;
			speed = i_speed;
			currentVelocity = Math::Vector3::ZERO;
		}

		Math::Vector3 Physics::PhysicsBody::CalculateDrag() const{
			Math::Vector3 drag = currentVelocity*currentVelocity*dragCoefficient;
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
			Math::Vector3 dragForce = CalculateDrag();
			if (isinf(dragForce.X())) {
				int a = 0;
			}
			Pointer::SmartPointer<Actor> smartPtr = weakPointer.Acquire();
			Math::Vector3 netForce = smartPtr->GetForward() * speed + dragForce + (useGravity ? GRAVITY : Math::Vector3::ZERO);
			Math::Vector3 acceleration = netForce / mass;
			Math::Vector3 previousVelocity = currentVelocity;
			currentVelocity = previousVelocity + acceleration * deltaTime;
			currentVelocity = currentVelocity.SquareMagnitude() > 100000.0f ? previousVelocity : currentVelocity;
			Math::Vector3 newPosition = smartPtr->GetPosition() + ((previousVelocity + currentVelocity) / 2) * deltaTime;			
			smartPtr->SetPosition(newPosition);
		}

		Math::Vector3 PhysicsBody::GetVelocity() {
			return currentVelocity;
		}

		void PhysicsBody::SetVelocity(Math::Vector3& newVelocity) {
			currentVelocity = newVelocity;
		}
	}
}