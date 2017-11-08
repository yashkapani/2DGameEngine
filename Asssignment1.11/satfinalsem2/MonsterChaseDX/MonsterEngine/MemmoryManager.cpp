#include "MemoryManager.h"
#include "malloc.h"
#include "Assert.h"
#include <stdio.h>
#include <new>
#include <cmath>


MemoryManager::MemoryManager(void * iMem, size_t i_Size) :pMyMem(iMem), mSize(i_Size)
{
	
	FreeList = reinterpret_cast<BlockDesc *>(pMyMem);
	FreeList->size = mSize;
	FreeList->next = NULL;
	availableMemory = mSize - sizeof(BlockDesc);
	//	BlockDesc * header = reinterpret_cast<BlockDesc *>(pMyMem);
	//	header->size = HeapSize;
	//	header->allocated = false;
	//header->address = pMyMem;

}

MemoryManager* MemoryManager::create(size_t HeapSize)
{
	void * imem = _aligned_malloc(HeapSize, 4);
	void * UserMemory = reinterpret_cast<char *>(imem)+sizeof(MemoryManager);

	return new (imem)MemoryManager(UserMemory, HeapSize);
};

void* MemoryManager::alloc(size_t size)
{


	using namespace std;
	if (size > availableMemory)
		return NULL;
	BlockDesc * previous = FreeList;
	BlockDesc * temp = FreeList;
	while (temp != NULL)
	{
		if (size < (temp->size - sizeof(BlockDesc)))
		{
			BlockDesc * remaining = reinterpret_cast<BlockDesc*>(reinterpret_cast<char *>(temp)+size + (size % 4) + sizeof(BlockDesc));
			remaining->next = temp->next;
			if (temp == FreeList)
				FreeList = remaining;
			else
				previous->next = remaining;

			BlockDesc * add = reinterpret_cast<BlockDesc*>(reinterpret_cast<char *>(temp)+sizeof(BlockDesc));
			add->size = size + sizeof(BlockDesc)+(size % 4);
			return reinterpret_cast<void*>(add);
		}
		previous = temp;
		temp = temp->next;
	}
	return NULL;
	/*//bestfit allocation
	BlockDesc * previous = NULL;
	BlockDesc * bestprevious = NULL;
	BlockDesc * bestfit = NULL;
	BlockDesc * temp = FreeList;

	while (temp != NULL)
	{
	if (bestfit == NULL)
	{
	if (size <= (temp->size - sizeof(BlockDesc)))
	{
	bestprevious = previous;
	bestfit = temp;
	}
	}
	else
	{
	if (size <= (temp->size - sizeof(BlockDesc)) && temp->size < bestfit->size)
	{
	bestfit = temp;
	bestprevious = previous;
	}
	}

	previous = temp;
	temp = temp->next;
	}

	//if no block is large enough
	if (bestfit == NULL)
	return NULL;

	//Alligned malloc
	size_t totalsize = size + sizeof(BlockDesc);
	size_t pad = totalsize % 4;

	if (bestfit == FreeList && bestprevious == NULL)
	{
	FreeList = reinterpret_cast<BlockDesc*>(reinterpret_cast<char *>(bestfit)+size + pad + sizeof(BlockDesc));
	}
	else
	{
	assert(bestprevious);
	BlockDesc *remainingBlock = reinterpret_cast<BlockDesc*>(reinterpret_cast<char *>(bestfit)+size + pad + sizeof(BlockDesc));
	remainingBlock->allocated = false;
	remainingBlock->size = bestfit->size -( size + pad + sizeof(BlockDesc));
	remainingBlock->next = bestfit->next;

	bestprevious->next = remainingBlock;
	}

	BlockDesc * head = reinterpret_cast<BlockDesc*>(bestfit);
	head->size = size + sizeof(BlockDesc);
	head->allocated = true;

	bestfit = reinterpret_cast<BlockDesc*>(reinterpret_cast<char *>(bestfit)+sizeof(BlockDesc));
	void * add = reinterpret_cast<void*>(bestfit);
	head->address = add;
	availableMemory = availableMemory - head->size;*/

}

void MemoryManager::_free(void * addptr)
{
	BlockDesc * header = reinterpret_cast<BlockDesc *>(reinterpret_cast<char *>(addptr)-sizeof(BlockDesc));
	size_t tsize = header->size;

	BlockDesc * temp = reinterpret_cast<BlockDesc *>(header);
	BlockDesc * previous = FreeList;
	//add new block to link list in sorted order
	if (temp < FreeList)
	{
		temp->next = FreeList;
		FreeList = temp;
	}
	else
	{

		BlockDesc * searchlist = FreeList->next;
		while (searchlist != NULL)
		{
			if (temp < searchlist)
			{
				previous->next = temp;
				temp->next = searchlist;
			}

			previous = searchlist;
			searchlist->next = previous;
		}

		if (searchlist == NULL)
		{
			previous->next = temp;
			temp->next = NULL;
		}
	}

	availableMemory = availableMemory + tsize;
	garbagecollection(previous, temp);
}

void MemoryManager::garbagecollection(BlockDesc * previous, BlockDesc * current)
{
	BlockDesc * temp = reinterpret_cast<BlockDesc *>(reinterpret_cast<char *>(previous)+previous->size);

	if (temp == current)
	{
		previous->size += current->size;
		previous->next = current->next;
		current = previous;
	}

	temp = reinterpret_cast<BlockDesc *>(reinterpret_cast<char *>(current)+current->size);
	if (temp == current->next)
	{
		current->size += (current->next)->size;
		current->next = (current->next)->next;
	}
}

MemoryManager::~MemoryManager()
{
	void * MemToFree = reinterpret_cast<char *>(pMyMem)-sizeof(MemoryManager);
	_aligned_free(MemToFree);
}












