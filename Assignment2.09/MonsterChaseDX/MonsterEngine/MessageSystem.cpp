#include "MessageSystem.h"

namespace Engine
{


	std::map< HashedString, std::vector<MessageSystem::IMessageHandler *> > MessageSystem::m_MessageHandlers;

	void Engine::MessageSystem::AddMessageHandler(const HashedString & i_Message, IMessageHandler * i_pHandler) {

		m_MessageHandlers[i_Message].push_back(i_pHandler);
	}

	void Engine::MessageSystem::SendMessage(const HashedString & i_Message, void * i_pMessageSender, void * i_pMessageData) {

		for (size_t i = 0; i < m_MessageHandlers[i_Message].size(); i++)
		{
			m_MessageHandlers[i_Message][i]->HandleMessage(i_Message, NULL, i_pMessageData);
		}

	}

}