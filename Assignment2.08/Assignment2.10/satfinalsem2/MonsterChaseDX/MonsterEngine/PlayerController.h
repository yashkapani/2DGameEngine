
#include "IAController.h"
#include "Messagesys.h"


namespace Engine{
	class PlayerController : public IAController, public MessageSystem::IMessageHandler
	{
	private:
		char Key;
	public:
		~PlayerController(){}
		PlayerController() { Key = 0; }
		void UpdateActor(Vector3 & i_Acceleration);
		void HandleMessage(const HashedString & i_Message, void * i_pData);
	};
}