#include "PlayerController.h"

namespace Engine
{
	void PlayerController::UpdateActor(Vector3 & i_Acceleration)
	{
		switch (Key)
		{
		case 'w':
			i_Acceleration = Vector3(-0.0001f, 0.0f, 0.0f);
			break;
		case 'a':
			i_Acceleration = Vector3(0.0001f, 0.0f, 0.0f);
			break;
		case 's':
			i_Acceleration = Vector3(0.0f, 0.0001f, 0.0f);
			break;
		case 'd':
			i_Acceleration = Vector3(0.0f, -0.0001f, 0.0f);
			break;
		default:
			break;
		}
		Key = 0;
	}

	void PlayerController::HandleMessage(const Engine::HashedString & i_Message, void* i_pData)
	{
		if (i_pData == NULL)
			Key = 0;
		else
			PlayerController::Key = *reinterpret_cast<char *>(i_pData);
	}
}