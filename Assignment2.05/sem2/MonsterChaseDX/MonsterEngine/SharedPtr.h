#ifndef __SharedPtr_H
#define __SharedPtr_H

#include <stdint.h>
#include <stdlib.h>

namespace Engine
{
	template <class T>
	class SharedPtr
	{
	public:
		SharedPtr() {}
		explicit SharedPtr(T* i_ptr);

		SharedPtr(SharedPtr & i_ptr);
		SharedPtr & operator =(SharedPtr & i_ptr);

		~SharedPtr();

		T* operator ->();
		T & operator *();

	private:
		T* m_ptr;
		uint32_t * m_pRefCount;
	};
}

#include "SharedPtr.inl"

#endif

