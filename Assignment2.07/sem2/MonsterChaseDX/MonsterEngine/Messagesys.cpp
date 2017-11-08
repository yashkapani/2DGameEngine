#include "Messagesys.h"
namespace Engine
{
	std::map< HashedString, std::vector<MessageSystem::IMessageHandler *> > MessageSystem::m_MessageHandlers;
	void MessageSystem::AddMessageHandler(const HashedString & i_Message, IMessageHandler * i_pHandler)
	{
		m_MessageHandlers[i_Message].push_back(i_pHandler);
	}

	void MessageSystem::SendMessage(const HashedString & i_Message, void * i_pData)
	{
		std::vector<IMessageHandler *> pHandlers = m_MessageHandlers[i_Message];
		for (size_t i = 0; i < pHandlers.size(); i++)
			pHandlers[i]->HandleMessage(i_Message, i_pData);
	}
}