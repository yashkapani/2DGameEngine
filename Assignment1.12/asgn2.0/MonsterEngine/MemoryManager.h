#pragma once
#include "BlockDescriptor.h"
#include "Assert.h"
#include <assert.h>

class MemoryManager
{
private:
	int blocksize;
	int memorysize;
	void * startaddress;
	BlockDescriptor * MemoryBlock;
	
public:
	void* operator new(size_t i);
	void operator delete(void* ptr);
	void* alloc(size_t i);
	void _free(void * i_pmem);
	void garbageCollect();

	MemoryManager();
	MemoryManager(size_t i_size, void* i_startadress);
	~MemoryManager();
	static MemoryManager* newMemory(size_t);
	static void deleteMemory(MemoryManager* i_ptr)
	{
		i_ptr->MemoryManager::~MemoryManager();
	}

	
	bool contains(void * i_ptr);
	unsigned int no_freeblocks();
	int getSize(){ return memorysize; }


};










































