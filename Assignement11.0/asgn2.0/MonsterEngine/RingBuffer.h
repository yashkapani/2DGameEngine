#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H
#include "MemoryManager.h"
#include "ConsolePrint.h"

template <class T>
class RingBuffer
{
public:
	static RingBuffer<T> * create(size_t i_Size);
	T operator[] (size_t i_index);
	void push(T i_Element);
	~RingBuffer();
	size_t getTotal() { return m_Total; }
private:
	T * m_pBuffer;
	T * m_pCurrentPosition;
	size_t m_Total;
	size_t m_Max;
	RingBuffer<T>(T * i_pMemory, size_t i_Size);
};

#include "RingBuffer.inl"

#endif 