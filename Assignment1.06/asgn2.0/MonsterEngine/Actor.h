#ifndef _ACTOR_H
#define _ACTOR_H
#include <string.h>
#include "Vector3.h"


	class Actor
	{
	public:
		Actor()
		{
			m_Position = Vector3(0.0f, 0.0f, 0.0f);
			m_Velocity = Vector3(1.0f, 1.0f, 1.0f);
			m_name = "Monster";
			

		}
		Actor(const Vector3 & i_InitialPosition, const Vector3 & i_InitialVelocity, const char* p_name) :
			m_bIsDead(false),
			m_Position(i_InitialPosition),
			m_Velocity(i_InitialVelocity),
			m_name(_strdup(p_name))
		{
		}
		
		~Actor()
		{
			if (m_name)
				delete[] (m_name);
		}
		void Kill() { m_bIsDead = true; }
		bool IsDead() const { return m_bIsDead; }

		void SetPosition(const Vector3 & i_Position) { m_Position = i_Position; }
		void SetVelocity(const Vector3 & i_Velocity) { m_Velocity = i_Velocity; }
		

		// return by reference or value??
		const Vector3 & GetPosition(void) const { return m_Position; }
		const Vector3 & GetVelocity(void) const { return m_Velocity; }
		const char * GetName(){ return m_name; }
		void Update() { m_Position = m_Position + m_Velocity; }
		
	private:
		bool					m_bIsDead;
		const char * m_name;
		Vector3				m_Position;
		Vector3				m_Velocity;
		

	};


#endif