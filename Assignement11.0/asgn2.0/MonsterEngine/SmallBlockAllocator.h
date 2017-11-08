#ifndef _SmallBlockAllocator_H
#define _SmallBlockAllocator_H
#include "BitField.h"

class SmallBlockAllocator
{

public:
	static SmallBlockAllocator * create(size_t i_blockSize, size_t i_blockCount);
	~SmallBlockAllocator();
	void * _alloc(size_t i_size);
	void _free(void * i_pmem);
	bool Contains(void * i_ptr);
	unsigned int blocksFree();
private:
	SmallBlockAllocator(size_t i_blockSize, size_t i_blockCount, void * i_pMemory, BitField * i_pBitField);
	void * m_pMemory;
	size_t m_BlockCount;
	size_t m_BlockSize;
	BitField * m_pBitField;
};
#endif //_SmallBlockAllocator_H