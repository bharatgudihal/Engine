#pragma once
#include "../Actor/Actor.h"
#include "../Renderer/Renderer.h"
#include "../Physics/PhysicsBody.h"
#include "../Utility/Utility.h"
#include "../Lua/LuaHelper.h"
#include "../Controllers/ActorController.h"
#include "../String/ConstantStrings.h"
#include "../Renderer/RenderObject.h"
#include "../Physics/PhysicsBody.h"
namespace Engine {
	namespace GameObject {
		class GameObject {
		public:
			static GameObject* Create(const char*);
			~GameObject();
			void Update(float);			
		private:
			GameObject(Pointer::SmartPointer<Actor> i_actor, Renderer::RenderObject* i_renderObject = nullptr, Physics::PhysicsBody* i_physicsBody = nullptr, IActorController* i_controller = nullptr);
			Pointer::SmartPointer<Actor> actor;
			Renderer::RenderObject* renderObject;
			Physics::PhysicsBody* physicsBody;
			IActorController* controller;
		};
	}
}