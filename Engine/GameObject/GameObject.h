#pragma once
#include "../Actor/Actor.h"
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
			static GameObject* Create(uint8_t* fileData, uint32_t fileSize);
			static GameObject* Create(LuaHelper::LuaHelper*);
			~GameObject();
			void SetController(IActorController*);
			inline Pointer::SmartPointer<Actor>* GetActorReference();			
			inline const Renderer::RenderObject* GetRenderObject();
			inline IActorController* GetController();
			inline Physics::PhysicsBody* GetPhysicsBody();
		private:
			GameObject(Pointer::SmartPointer<Actor> i_actor, Renderer::RenderObject* i_renderObject = nullptr, Physics::PhysicsBody* i_physicsBody = nullptr, IActorController* i_controller = nullptr);
			Pointer::SmartPointer<Actor> actor;
			Renderer::RenderObject* renderObject;
			Physics::PhysicsBody* physicsBody;
			IActorController* controller; 
		};
	}
}
#include "GameObject_Inl.h"