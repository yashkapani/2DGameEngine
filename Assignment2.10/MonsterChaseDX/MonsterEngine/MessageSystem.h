#ifndef __MESSAGE_SYSTEM_H
#define __MESSAGE_SYSTEM_H
#include "HashedString.h"
#include <map>
#include <vector>


namespace Engine
{

	class MessageSystem
	{
	public:

		class IMessageHandler
		{
		public:
			virtual ~IMessageHandler();

			virtual void HandleMessage(const HashedString & i_Message, void * i_pMessageSender, void * i_pMessageData) = 0;
		};

		static void AddMessageHandler(const HashedString & i_Message, IMessageHandler * i_pHandler);
		static void SendMessage(const HashedString & i_Message, void * i_pMessageSender, void * i_pMessageData);

	private:
		static std::map< HashedString, std::vector<IMessageHandler *> > 	m_MessageHandlers;
	};

} // namespace Engine

#endif // __MESSAGE_SYSTEM_H