#pragma once
namespace Engine {
	namespace GameObject {
		inline Pointer::SmartPointer<Actor>* GameObject::GetActorReference(){
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

		inline IActorController* GameObject::GetController() const{
			return controller;
		}

		inline Physics::PhysicsBody* GameObject::GetPhysicsBody() const{
			return physicsBody;
		}

		inline void GameObject::SetPhysicsBody(Physics::PhysicsBody* newPhysicsBody) {
			if (physicsBody) {
				delete physicsBody;
			}
			physicsBody = newPhysicsBody;
		}

		inline void GameObject::SetEnabled(bool i_enabled) {
			isEnabled = i_enabled;
		}

		inline const bool GameObject::GetEnabled() const{
			return isEnabled;
		}

		inline const uint8_t GameObject::GetUID() const {
			return UID;
		}
	}
}