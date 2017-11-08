#ifndef __AUTOPTR_H
#define __AUTOPTR_H

namespace Engine
{

	template <class T>
	class AutoPtr
	{
	public:

		//Constructors and Assignment Operator
		explicit AutoPtr(T* i_ptr);
		AutoPtr(AutoPtr & i_ptr);
		AutoPtr & operator=(AutoPtr & i_ptr);

		//Destructor
		~AutoPtr();

		//Pointer Operators
		T* operator ->();
		T& operator *();
	private:
		T* m_ptr;
	};
}

#include "AutoPtr.inl"

#endif 