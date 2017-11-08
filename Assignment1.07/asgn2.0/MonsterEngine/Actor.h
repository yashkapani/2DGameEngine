#ifndef _ACTOR_H
#define _ACTOR_H
#undef new
#include <string.h>
#include <assert.h>
#include "Vector3.h"
#include "SmallBlockAllocator.h"

	class Actor
	{
	public:
		static SmallBlockAllocator * s_pAllocator;


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
		
		void * operator new(size_t i_size)
		{
			if (s_pAllocator == NULL)
			s_pAllocator = SmallBlockAllocator::create(sizeof(Actor), 100);
			void * temp = s_pAllocator->_alloc(i_size);
			return temp;
		}
		void operator delete(void * i_ptr)
		{
			assert(s_pAllocator);
			if (s_pAllocator->Contains(i_ptr))
				s_pAllocator->_free(i_ptr);
			else
				free(i_ptr);
		}


		
	private:
		bool					m_bIsDead;
		const char * m_name;
		Vector3				m_Position;
		Vector3				m_Velocity;

		

	};

	
#endif