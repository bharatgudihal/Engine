#include "../MessagingSystem.h"

namespace Engine {
	namespace Messaging {

		MessageHandler::MessageHandler(const String::HashedString& i_message, IMessageHandler* i_handler):message(i_message),handler(i_handler){}

		bool MessageHandler::operator==(const MessageHandler& other) const {
			return other.message == message && other.handler == handler;
		}

		MessagingSystem* MessagingSystem::instance = nullptr;

		MessagingSystem::MessagingSystem() {}

		MessagingSystem::~MessagingSystem() {}

		bool MessagingSystem::Startup() {
			if (!instance) {
				instance = new MessagingSystem();
			}
			assert(instance);
			return true;
		}

		void MessagingSystem::ShutDown() {
			if (instance) {
				delete instance;
			}
		}

		MessagingSystem* MessagingSystem::GetInstance() {
			return instance;
		}

		void  MessagingSystem::RegisterMessageHandler(const String::HashedString& message, IMessageHandler* handler) {
			MessageHandler messageHandler(message, handler);
			messaginMutex.Acquire();
			messageHandlers.push_back(messageHandler);
			messaginMutex.Release();
		}

		void  MessagingSystem::DeRegisterMessageHandler(const String::HashedString& message, IMessageHandler* handler) {
			MessageHandler messageHandler(message, handler);
			messaginMutex.Acquire();
			for (int i = 0; i < messageHandlers.size(); i++) {
				if (messageHandlers[i] == messageHandler) {
					messageHandlers.erase(messageHandlers.begin() + i);					
					break;
				}
			}
			messaginMutex.Release();
		}

		void  MessagingSystem::SendMessageToHandler(const String::HashedString& message) {
			messaginMutex.Acquire();
			for (int i = 0; i < messageHandlers.size(); i++) {
				if (messageHandlers[i].message == message) {
					messageHandlers[i].handler->HandleMessage(message);
				}
			}
			messaginMutex.Release();
		}
	}
}