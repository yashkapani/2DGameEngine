#include"InputMove.h"


	using namespace std;
	

		void InputMove :: UpdateActor(Actor * i_pActor)
		{
			m_velocity = Vector3(0.0f, 0.0f, 0.0f);
			char ch;
			s1:
			cout << "Which direction you want Player to move \n Select 'r' for right \n 'l' for left and 'u' for up and 'd' for down"<<endl;
			cin >> ch;
			if (ch == 'r')
			{
				m_velocity.Y(1);
			}
			else if (ch == 'l')
			{
				m_velocity.Y(-1);
			}
			else if (ch == 'd')
			{
				m_velocity.X(1);
			}
			else if (ch == 'u')
			{
				m_velocity.X(-1);
			}
			else
			{
				cout << "Wrong Input \n " << endl;
				goto s1;
			}
			i_pActor->SetVelocity(m_velocity);
			i_pActor->Update();
			m_velocity = i_pActor->GetPosition();
			cout << "location of player is [" << m_velocity.X() <<"] ["<<m_velocity.Y()<<"]"<< endl;

		}
	

	
