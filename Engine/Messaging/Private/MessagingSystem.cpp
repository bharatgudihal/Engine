#include "../MessagingSystem.h"

namespace Engine {
	namespace Messaging {

		MessageHandler::MessageHandler(const String::HashedString& i_message, const Handler i_handler):message(i_message),handler(i_handler){}

		bool MessageHandler::operator==(const MessageHandler& other) const {
			return other.message == message && other.handler == handler;
		}

		static std::vector<MessageHandler> messageHandlers;

		void RegisterMessageHandler(const String::HashedString& message, Handler handler) {
			MessageHandler messageHandler(message, handler);
			messageHandlers.push_back(messageHandler);
		}

		void DeRegisterMessageHandler(const String::HashedString& message, Handler handler) {
			MessageHandler messageHandler(message, handler);
			for (int i = 0; i < messageHandlers.size(); i++) {
				if (messageHandlers[i] == messageHandler) {
					messageHandlers.erase(messageHandlers.begin() + i);
					break;
				}
			}
		}

		void SendMessage(const String::HashedString& message) {
			for (int i = 0; i < messageHandlers.size(); i++) {
				if (messageHandlers[i].message == message) {
					messageHandlers[i].handler(message);
				}
			}
		}
	}
}