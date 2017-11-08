#include "SmallBlockAllocator.h"
#include<cstdlib>
#include <stdio.h>
SmallBlockAllocator * SmallBlockAllocator::create(size_t i_blockSize, size_t i_blockCount)
{
	void * pMemory = malloc(i_blockSize * i_blockCount);

	if (pMemory == NULL)
		return NULL;
	BitField * pBitField = BitField::create(i_blockCount);
	if (pBitField == NULL)
	{
		free(pMemory);
		return NULL;
	}
	return new SmallBlockAllocator(i_blockSize, i_blockCount, pMemory, pBitField);
}
SmallBlockAllocator::SmallBlockAllocator(size_t i_blockSize, size_t i_blockCount, void * i_pMemory, BitField * i_pBitField)
{
	m_pMemory = i_pMemory;
	m_pBitField = i_pBitField;
	m_BlockCount = i_blockCount;
	m_BlockSize = i_blockSize;
}
SmallBlockAllocator::~SmallBlockAllocator()
{
	free(m_pMemory);
	delete m_pBitField;
}
void * SmallBlockAllocator::_alloc(size_t i_size)
{
	size_t index = 0;
	if (m_pBitField->findFirstFreeBit(index))
	{
		m_pBitField->setBit(index);
		return reinterpret_cast<void *>(reinterpret_cast<uint32_t *>(m_pMemory)+index * m_BlockSize);
	}
#ifdef _DEBUG
	std::cout<<"Small Block Allocator memory is full.\n";
#endif
	return NULL;
}

void SmallBlockAllocator::_free(void * i_pmem)
{
	size_t index = (reinterpret_cast<uint32_t *>(i_pmem)-reinterpret_cast<uint32_t *>(m_pMemory)) / m_BlockSize;
	m_pBitField->clearBit(index);
}

bool SmallBlockAllocator::Contains(void * i_ptr)
{
	size_t index = (reinterpret_cast<uint32_t *>(i_ptr)-reinterpret_cast<uint32_t *>(m_pMemory)) / m_BlockSize;
	if (index < 0 || index >= m_BlockCount)
		return false;
	return (*m_pBitField)[index];

}


unsigned int SmallBlockAllocator::blocksFree()
{
	unsigned int count = 0;
	for (size_t i = 0; i < m_BlockCount; i++){
		if ((*m_pBitField)[i] == false){
			count++;
		}
	}
	return count;

}