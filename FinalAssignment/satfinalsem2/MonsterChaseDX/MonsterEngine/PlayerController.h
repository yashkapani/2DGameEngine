
#include "IAController.h"
#include "MessageSystem.h"


namespace Engine{
	class PlayerController : public IAController, public MessageSystem::IMessageHandler
	{
	public:
		char Key;
		~PlayerController(){}
		PlayerController() { Key = 0; }
		void UpdateActor(Vector3 & i_Acceleration);
		void HandleMessage(const HashedString & i_Message, void * i_pData);
		
	};
}