#include"Random.h"


using namespace std;


void Random ::UpdateActor(Actor * i_pActor)
{
	m_velocity = Vector3(0.0f, 0.0f, 0.0f);

	m_velocity = Vector3(0.0f, 0.0f, 0.0f);
	m_velocity.X(rand() % 10);
	m_velocity.Y(rand() % 10);
	m_velocity.Z(rand() % 10);
	cout << "location of player is [" << m_velocity.X() << "] [" << m_velocity.Y() << "][" << m_velocity.Z() << endl;

}



