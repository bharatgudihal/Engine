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
			inline void SetRenderObject(Renderer::RenderObject*);
			inline IActorController* GetController() const;
			inline Physics::PhysicsBody* GetPhysicsBody() const;
			inline void SetPhysicsBody(Physics::PhysicsBody*);
			inline void SetEnabled(bool);
			inline const bool GetEnabled() const;
			inline const uint8_t GetUID() const;
		private:
			GameObject(Pointer::SmartPointer<Actor> i_actor, Renderer::RenderObject* i_renderObject = nullptr, Physics::PhysicsBody* i_physicsBody = nullptr, IActorController* i_controller = nullptr);
			Pointer::SmartPointer<Actor> actor;
			Renderer::RenderObject* renderObject;
			Physics::PhysicsBody* physicsBody;
			IActorController* controller; 
			bool isEnabled;
			uint8_t UID;
		};
	}
}
#include "GameObject_Inl.h"