#pragma once
#include "PooledString.h"
namespace Engine {
	namespace String {
		class ConstantStrings{
		public:
			inline static ConstantStrings* GetInstance();
			inline static bool Create();
			inline static void Destroy();
			const PooledString NAME;
			const PooledString CLASS;
			const PooledString CONTROLLER;
			const PooledString POSITION;
			const PooledString PHYSICSBODY;
			const PooledString RENDERSETTINGS;
			const PooledString PLAYER;
			const PooledString GAMEOBJECT;
			const PooledString PLAYERCONTROLLER;
			const PooledString MONSTERCONTROLLER;
			const PooledString MASS;
			const PooledString DRAG;
			const PooledString SPRITE;
			const PooledString FORCEMULTIPLIER;
			const PooledString AABB;
			const PooledString CENTER;
			const PooledString EXTENTS;
		private:
			ConstantStrings();
			~ConstantStrings();
			static ConstantStrings* instance;
		};
	}
}
#include "ConstantStrings_Inl.h"