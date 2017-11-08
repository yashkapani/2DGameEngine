#ifndef _BitField_H
#define _BitField_H
#include <iostream>
#include <stdint.h>
class BitField
{
public:
	static BitField * create(size_t i_blockCount);
	~BitField();
	bool operator[] (size_t i_index);
	bool findFirstFreeBit(size_t &i_index);
	bool findFirstSetBit(size_t &i_index);
	void setBit(size_t &i_index);
	void clearBit(size_t &i_index);
private:
	uint32_t * m_pBitField;
	size_t m_blockCount;
	BitField(size_t i_blockCount, size_t * i_pMemory);
};


#endif //_BitField_H