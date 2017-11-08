
#ifndef _RingBuffer_H
#define _RingBuffer_H

#pragma once
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "Vector3.h"
#include <vector>
#include <assert.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#pragma once
using namespace std;
template <class T>
class RingBuffer
{
private:
	size_t maxsize;
	vector<T> m_Items;
	size_t m_Current=0;
	bool flagoverflow;

public:

	RingBuffer<T>::RingBuffer(size_t i_Items)
	{
		maxsize = i_Items;
		m_Items = vector<T>(maxsize);
		m_Items.reserve(maxsize);
	}

	void RingBuffer<T>::add(T i_Item)
	{
		m_Items[m_Current] = i_Item;
		m_Current++;
		if (m_Current >= maxsize)
		{
			m_Current = 0;
			flagoverflow = true;
		}
	}

	size_t RingBuffer<T>::size()
	{
		return maxsize;
	}

	int RingBuffer<T>::count()
	{
		if (flagoverflow)
			return maxsize;
		else
			return m_Current;
	}

	const T& RingBuffer<T>::operator[](size_t i_Index)
	{
		assert(i_Index <= maxsize);
		if (m_Current >= i_Index)
		{
			return m_Items[m_Current - i_Index];
		}
		else
		{
			if (flagoverflow)
			{
				return m_Items[maxsize + (m_Current - i_Index)];
			}
			
		}
	}
	
};
#endif
