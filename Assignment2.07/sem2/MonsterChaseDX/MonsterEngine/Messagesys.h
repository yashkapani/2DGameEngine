#ifndef __MESSAGESYSTEM_H
#define __MESSAGESYSTEM_H

#include <map>
#include <vector>

#include "HashedString.h"

namespace Engine
{
	class MessageSystem
	{
	public:
		class IMessageHandler
		{
		public:
			virtual ~IMessageHandler() {}
			virtual void HandleMessage(const HashedString & i_Message, void * i_pData) = 0;
		};
		static void AddMessageHandler(const HashedString & i_Message, IMessageHandler * i_pHandler);
		static void SendMessage(const HashedString & i_Message, void * i_pData);
	private:
		static std::map< HashedString, std::vector<IMessageHandler *> > m_MessageHandlers;

	};
}

#endif 
