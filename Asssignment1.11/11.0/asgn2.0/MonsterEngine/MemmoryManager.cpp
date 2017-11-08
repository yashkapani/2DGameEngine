#include "MemoryManager.h"
#include "malloc.h"
#include <stdio.h>
#include <new>
#include <cmath>

MemoryManager::MemoryManager() 
{
	memorysize = 0;
	startaddress = nullptr;

}

MemoryManager::MemoryManager(size_t i_size, void* i_startadress)
{
	memorysize = i_size;
	startaddress = i_startadress;
	blocksize =8;
	size_t no = memorysize / blocksize;
	MemoryBlock = (BlockDescriptor*)_aligned_malloc(sizeof(BlockDescriptor)*no, 4);


	for (int i = 0; i < no; i++)
	{
		(MemoryBlock + i)->BlockDescriptor::BlockDescriptor();
		void* newAddress = (char*)startaddress + blocksize*i;
		MemoryBlock[i].setAddress(newAddress);
		MemoryBlock[i].setNextFree(1);
		MemoryBlock[i].setTotalEmpty(no - i);
		if (i == 0)
		{
			MemoryBlock[i].setTotalEmpty(0);


		}
	}
}



	MemoryManager::~MemoryManager()
	{
		_aligned_free(MemoryBlock);
		_aligned_free(startaddress);

	}

	void MemoryManager::garbageCollect()
	{
		size_t count = memorysize / blocksize;
		for (size_t i = count - 1; i > 0; i--)
		{
			if (MemoryBlock[i].getTotalEmpty() == 1)
			{
				int temp = MemoryBlock[i - 1].getTotalEmpty();
				MemoryBlock[i].setTotalEmpty(temp + 1);
			}
		}
	}



MemoryManager* MemoryManager::newMemory(size_t i_bsize)
		{
			void* pMemory = _aligned_malloc(i_bsize, 64);

			if (pMemory == nullptr)
				return NULL;

			MemoryManager* pManager = (MemoryManager*)_aligned_malloc(sizeof(MemoryManager), 4);
			pManager->MemoryManager::MemoryManager(i_bsize, pMemory);
			return pManager;
		}


void MemoryManager::_free(void * i_pmem)
{
	size_t no = memorysize / blocksize;

	for (size_t i = 0; i < no; i++)
	{
		if (MemoryBlock[i].getAddress() == i_pmem){
			for (int j = 0; j < MemoryBlock[i].getNextFree(); j++){
				MemoryBlock[i + j].setTotalEmpty(1);
			}
			MemoryBlock[i].setNextFree(1);
		}
	}
}

void* MemoryManager::alloc(size_t i_size){
	if (i_size > memorysize)
	{
		return NULL;
	}

	int numofBlocks = ceil(i_size / blocksize);
	

	size_t count = memorysize / blocksize;

	for (size_t i = 0; i < count; i++)
	{
		if (MemoryBlock[i].getTotalEmpty() > numofBlocks)
		{
			for (int j = 0; j < numofBlocks; j++){
				MemoryBlock[i + j].setTotalEmpty(0);
			}
			MemoryBlock[i].setNextFree(numofBlocks);
			return MemoryBlock[i].getAddress();
		}
	}
	return NULL;
};

		
















