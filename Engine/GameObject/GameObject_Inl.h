#pragma once
namespace Engine {
	namespace GameObject {
		inline Pointer::SmartPointer<Actor>* GameObject::GetActorReference() {
			return &actor;
		}
	}
}