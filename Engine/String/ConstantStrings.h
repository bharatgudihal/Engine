#pragma once
#include "PooledString.h"
namespace Engine {
	namespace String {
		class ConstantStrings{
		public:
			static ConstantStrings* GetInstance();
			const PooledString NAME;
			const PooledString CLASS;
			const PooledString CONTROLLER;
			const PooledString POSITION;
			const PooledString PHYSICSBODY;
			const PooledString RENDERSETTINGS;
			const PooledString PLAYER;
			const PooledString PLAYERCONTROLLER;
			const PooledString MASS;
			const PooledString DRAG;
			const PooledString SPRITE;
			const PooledString FORCEMULTIPLIER;
		private:
			ConstantStrings();
			static ConstantStrings* instance;
		};
	}
}