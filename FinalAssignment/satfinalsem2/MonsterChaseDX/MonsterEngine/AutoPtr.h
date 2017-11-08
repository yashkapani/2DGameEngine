#ifndef GUARD_AutoPtr_h
#define GUARD_AutoPtr_h

#include <assert.h>

template<class T>
class AutoPtr
{
public:

	explicit AutoPtr(T * i_ptr) :
		m_ptr(i_ptr)
	{
	}

	~AutoPtr()
	{
		if (m_ptr)
			delete m_ptr;
	}

	T* operator->()
	{
		return m_ptr;
	}

	T& operator*()
	{
		assert(m_ptr);

		return *m_ptr;
	}
private:

	T * 	m_ptr;

};
#endif // GUARD_AutoPtr_h	