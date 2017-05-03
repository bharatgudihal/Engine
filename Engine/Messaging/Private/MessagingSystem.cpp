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
			messageHandlers[message].push_back(messageHandler);
			messaginMutex.Release();
		}

		void  MessagingSystem::DeRegisterMessageHandler(const String::HashedString& message, IMessageHandler* handler) {
			MessageHandler messageHandler(message, handler);
			messaginMutex.Acquire();
			std::vector<MessageHandler> vector = messageHandlers[message];
			vector.erase(std::remove(vector.begin(), vector.end(), messageHandler), vector.end());
			messaginMutex.Release();
		}

		void  MessagingSystem::SendMessageToHandler(const String::HashedString& message) {
			messaginMutex.Acquire();
			std::vector<MessageHandler> vector = messageHandlers[message];
			for (size_t i = 0; i < vector.size(); i++) {
				vector[i].handler->HandleMessage(message);
			}
			messaginMutex.Release();
		}
	}
}