#pragma once
namespace Engine {
	namespace GameObject {
		inline Pointer::SmartPointer<Actor>* GameObject::GetActorReference() {
			return &actor;
		}

		inline const Renderer::RenderObject* GameObject::GetRenderObject() {
			return renderObject;
		}

		inline IActorController* GameObject::GetController() {
			return controller;
		}

		inline Physics::PhysicsBody* GameObject::GetPhysicsBody() {
			return physicsBody;
		}
	}
}