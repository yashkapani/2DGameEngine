#include "Assert.h"

namespace Engine
{
	template <class T>
	inline SharedPtr<T>::SharedPtr(T* i_ptr) : m_ptr(i_ptr), m_pRefCount(new uint32_t(1))
	{ }

	template <class T>
	inline SharedPtr<T>::~SharedPtr()
	{
		MessagedAssert(m_pRefCount != NULL, "");
		if (--(*m_pRefCount) == 0)
		{
			if (m_ptr)
				delete m_ptr;
			delete m_pRefCount;
		}
	}

	template <class T>
	inline SharedPtr<T>::SharedPtr(SharedPtr<T> & i_ptr) : m_ptr(i_ptr.m_ptr), m_pRefCount(i_ptr.m_pRefCount)
	{
		MessagedAssert(m_pRefCount != NULL, "");
		(*m_pRefCount)++;
	}

	template <class T>
	inline SharedPtr<T> & SharedPtr<T>::operator = (SharedPtr & i_ptr)
	{
		MessagedAssert(m_pRefCount != NULL, "");

		if (--(*m_RefCount) == 0)
		{
			if (m_ptr)
				delete m_ptr;
			delete m_pRefCount;
		}

		m_ptr = i_ptr.m_ptr;
		m_pRefCount = i_ptr.m_pRefCount;
		(*m_pRefCount)++;

		return *this;
	}

	template <class T>
	inline T* SharedPtr<T>::operator ->()
	{
		return m_ptr;
	}

	template <class T>
	inline T& SharedPtr<T>::operator *()
	{
		MessagedAssert(m_ptr, "");
		return *m_ptr;
	}
}