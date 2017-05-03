#pragma once
#include <functional>
#include <map>
#include <vector>
#include "../String/HashedString.h"
#include "../Threading/Mutex.h"

namespace Engine {
	namespace Messaging {
		
		class IMessageHandler {
		public:
			~IMessageHandler() {};
			virtual void HandleMessage(const String::HashedString&) = 0;
		};

		class MessageHandler {
		public:
			MessageHandler(const String::HashedString&, IMessageHandler*);
			String::HashedString message;
			IMessageHandler* handler;
			bool operator==(const MessageHandler&) const;
		};

		class MessagingSystem {
		public:
			static bool Startup();
			static void ShutDown();
			static MessagingSystem* GetInstance();
			void RegisterMessageHandler(const String::HashedString&, IMessageHandler*);
			void DeRegisterMessageHandler(const String::HashedString&, IMessageHandler*);
			void SendMessageToHandler(const String::HashedString&);
		private:
			MessagingSystem();
			~MessagingSystem();
			static MessagingSystem* instance;
			std::map<String::HashedString, std::vector<MessageHandler>> messageHandlers;
			Threading::Mutex messaginMutex;
		};
	}
}