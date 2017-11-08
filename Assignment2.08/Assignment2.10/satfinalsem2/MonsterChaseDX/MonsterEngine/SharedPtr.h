#ifndef GUARD_SharedPtr_h
#define GUARD_SharedPtr_h

#include <assert.h>
#include <stdint.h>
namespace Engine
{

	template<class T>
	class SharedPtr
	{
	public:
		SharedPtr() {};
		explicit SharedPtr(T * i_ptr) :
			m_ptr(i_ptr), m_pRefCount(new uint32_t(1))
		{

		}

		SharedPtr(const SharedPtr & i_other) :
			m_ptr(i_other.m_ptr),
			m_pRefCount(i_other.m_pRefCount)
		{
			
			(*m_pRefCount)++;
		}

		SharedPtr & operator=(SharedPtr & i_other)
		{
			assert(m_pRefCount != NULL);

			if (--(*m_pRefCount) == 0)
			{
				if (m_ptr)
					delete m_ptr;
				delete m_pRefCount;
			}

			m_ptr = i_other.m_ptr;
			m_pRefCount = i_other.m_pRefCount;

			(*m_pRefCount)++;
			return *this;
		}

		inline ~SharedPtr()
		{
			
			if (--(*m_pRefCount) == 0)
			{
				if (m_ptr)
					delete m_ptr;
				delete m_pRefCount;
			}
		}

		inline T * operator->()
		{
			return m_ptr;
		}

		inline T & operator*()
		{
			MessagedAssert(m_ptr, "");

			return *m_ptr;
		}

		// release();
		// change( T * i_newptr );

	private:
		T * 		m_ptr;
		uint32_t*	m_pRefCount;
	}; // namespace Engine


	//#include "SharedPtr.inl"

}

#endif // GUARD_SharedPtr_h