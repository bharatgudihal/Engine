#pragma once
namespace Engine {
	namespace GameObject {
		inline Pointer::SmartPointer<Actor>* GameObject::GetActorReference() {
			return &actor;
		}

		inline const Renderer::RenderObject* GameObject::GetRenderObject() {
			return renderObject;
		}

		inline void GameObject::SetRenderObject(Renderer::RenderObject* newRenderer) {
			if (renderObject) {
				delete renderObject;
			}
			renderObject = newRenderer;
		}

		inline IActorController* GameObject::GetController() {
			return controller;
		}

		inline Physics::PhysicsBody* GameObject::GetPhysicsBody() {
			return physicsBody;
		}

		inline void GameObject::SetPhysicsBody(Physics::PhysicsBody* newPhysicsBody) {
			if (physicsBody) {
				delete physicsBody;
			}
			physicsBody = newPhysicsBody;
		}
	}
}