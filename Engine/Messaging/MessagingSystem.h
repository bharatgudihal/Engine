#pragma once
#include <functional>
#include <vector>
#include "../String/HashedString.h"

namespace Engine {
	namespace Messaging {
		typedef void(*Handler)(const String::HashedString&);
		void RegisterMessageHandler(const String::HashedString&, Handler);
		void DeRegisterMessageHandler(const String::HashedString&, Handler);
		void SendMessage(const String::HashedString&);
		class MessageHandler {
		public:
			MessageHandler(const String::HashedString&, const Handler);
			String::HashedString message;
			Handler handler;
			bool operator==(const MessageHandler&) const;
		};
	}
}