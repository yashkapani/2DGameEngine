#include "BitField.h"
#include <assert.h>

bool BitField::operator[](size_t i_index)
{
	size_t element = i_index / (sizeof(m_pBitField[0]) * 8);
	uint32_t value = m_pBitField[element];
	size_t offset = i_index - (element * sizeof(m_pBitField[0]) * 8);
	bool isSet = !!(value & (1 << offset));
	return isSet;
}
bool BitField::findFirstFreeBit(size_t &i_index)
{
	unsigned int offset = 0;
	size_t i = 0;
	while (m_pBitField[i] == UINT32_MAX)
		i++;

	uint32_t value = m_pBitField[i];

	while (offset < sizeof(m_pBitField[0]) * 8){
		if ((value & 1) == 0){
			i_index = (i * sizeof(m_pBitField[0]) * 8) + offset;
			return true;
		}
		else{
			value = value >> 1;
			offset++;
		}
	}

	return true;
}

bool BitField::findFirstSetBit(size_t &i_index)
{
	unsigned int offset = 0;
	size_t i = 0;
	while (m_pBitField[i] == UINT32_MAX)
		i++;

	uint32_t value = m_pBitField[i];

	while (offset < sizeof(m_pBitField[0]) * 8){
		if ((value & 1) == 1){
			i_index = (i * sizeof(m_pBitField[0]) * 8) + offset;
			return true;
		}
		else{
			value = value >> 1;
			offset++;
		}
	}

	return true;
}

void BitField::setBit(size_t &i_index)
{

	assert(i_index < m_blockCount);
	size_t element = i_index / (sizeof(m_pBitField[0]) * 8);
	size_t offset = i_index - (element * sizeof(m_pBitField[0]) * 8);

	m_pBitField[element] |= (1 << offset);
}

void BitField::clearBit(size_t &i_index)
{
	assert(i_index < m_blockCount);
	size_t element = i_index / (sizeof(m_pBitField[0]) * 8);
	size_t offset = i_index - (element * sizeof(m_pBitField[0]) * 8);

	m_pBitField[element] &= ~(1 << offset);
}

BitField * BitField::create(size_t i_blockCount)
{
	size_t * pMemory = (size_t *)_aligned_malloc(i_blockCount / 8, 64);
	if (pMemory == NULL)
		return NULL;

	return new BitField(i_blockCount, pMemory);
}

BitField::BitField(size_t i_blockCount, size_t * i_pMemory)
{
	m_pBitField = i_pMemory;
	m_blockCount = i_blockCount;
}

BitField::~BitField()
{
	_aligned_free(m_pBitField);
}