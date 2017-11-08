#include "Assert.h"

namespace Engine
{
	template <class T>
	inline AutoPtr<T>::AutoPtr(T* i_ptr) : m_ptr(i_ptr)
	{}

	template <class T>
	inline AutoPtr<T>::AutoPtr(AutoPtr<T> & i_ptr) : m_ptr(i_ptr.m_ptr)
	{
		i_ptr.m_ptr = NULL;
	}

	template <class T>
	inline AutoPtr<T> & AutoPtr<T>::operator=(AutoPtr<T> & i_ptr)
	{
		if (m_ptr)
			delete m_ptr;
		m_ptr = i_ptr.m_ptr;
		i_ptr.m_ptr = NULL;

		return *this;
	}

	template <class T>
	inline AutoPtr<T>::~AutoPtr()
	{
		if (m_ptr)
			delete m_ptr;
	}

	template <class T>
	inline T* AutoPtr<T>::operator -> ()
	{
		return m_ptr;
	}

	template <class T>
	inline T& AutoPtr<T>::operator * ()
	{
		MessagedAssert(m_ptr, "");
		return *m_ptr;
	}
}