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
			const PooledString GAMEOBJECT;
			const PooledString MASS;
			const PooledString DRAG;
			const PooledString SPRITE;
			const PooledString FORCEMULTIPLIER;
			const PooledString AABB;
			const PooledString CENTER;
			const PooledString EXTENTS;
			const PooledString COUNT;
			const PooledString ISENABLED;
			const PooledString TRUE_STRING;
			const PooledString FALSE_STRING;
		private:
			ConstantStrings();
			~ConstantStrings();
			static ConstantStrings* instance;
		};
	}
}
#include "ConstantStrings_Inl.h"