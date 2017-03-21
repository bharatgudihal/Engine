#include "../GameObject.h"
namespace Engine {
	namespace GameObject {
		GameObject* GameObject::Create(uint8_t* fileData, uint32_t fileSize) {
			LuaHelper::LuaHelper luaHelper(fileData, fileSize);
			return Create(&luaHelper);
		}

		GameObject* GameObject::Create(LuaHelper::LuaHelper* luaHelper) {
			luaHelper->LoadGlobalTable(String::ConstantStrings::GetInstance()->GAMEOBJECT.Get());
			String::PooledString name = luaHelper->GetStringFromTable(String::ConstantStrings::GetInstance()->NAME.Get(), -1);
			Math::Vector3 position;
			luaHelper->GetVector2DFromTable(String::ConstantStrings::GetInstance()->POSITION.Get(), position, -1);
			luaHelper->GetTableFromTable(String::ConstantStrings::GetInstance()->PHYSICSBODY.Get(), -1);
			float mass;
			luaHelper->GetFloatFromTable(String::ConstantStrings::GetInstance()->MASS.Get(), mass, -1);
			float drag;
			luaHelper->GetFloatFromTable(String::ConstantStrings::GetInstance()->DRAG.Get(), drag, -1);
			float forceMultiplier;
			luaHelper->GetFloatFromTable(String::ConstantStrings::GetInstance()->FORCEMULTIPLIER.Get(), forceMultiplier, -1);
			luaHelper->Pop();
			luaHelper->GetTableFromTable(String::ConstantStrings::GetInstance()->RENDERSETTINGS.Get(), -1);
			String::PooledString spritePath = luaHelper->GetStringFromTable(String::ConstantStrings::GetInstance()->SPRITE.Get(), -1);
			luaHelper->Pop();
			luaHelper->Pop();
			Pointer::SmartPointer<Actor> actor(new Actor(name.Get(), position));
			size_t fileSize;
			void* file = Utility::LoadFile(spritePath.Get(), fileSize);
			assert(file && fileSize);
			Renderer::RenderObject* renderObject = Renderer::RenderObject::Create(actor, file, fileSize);
			Physics::PhysicsBody* physicsBody = new Engine::Physics::PhysicsBody(actor, forceMultiplier, mass, drag);
			delete file;
			return new GameObject(actor, renderObject, physicsBody);
		}

		GameObject::GameObject(Pointer::SmartPointer<Actor> i_actor, Renderer::RenderObject* i_renderObject, Physics::PhysicsBody* i_physicsBody, IActorController* i_controller):actor(i_actor), renderObject(i_renderObject), physicsBody(i_physicsBody), controller(i_controller){
		}

		GameObject::~GameObject() {
			if (controller) {
				delete controller;
			}
			if (renderObject) {
				delete renderObject;
			}
			if (physicsBody) {
				delete physicsBody;
			}
		}

		void GameObject::SetController(IActorController* i_controller) {
			controller = i_controller;
		}
	}
}