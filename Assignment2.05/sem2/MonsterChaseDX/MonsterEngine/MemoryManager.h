
#ifndef _MEMORYMANAGER_H
#define _MEMORYMANAGER_H
struct list
{
	size_t size;
	list* next;

};

struct BlockDesc
{
	void * address;
	size_t size;
	bool allocated;
	BlockDesc *next;
};




class MemoryManager
{

public:
	~MemoryManager();
	static MemoryManager* create(size_t HeapSize);

	void* alloc(size_t size);
	void _free(void * addptr);
	void garbagecollection(BlockDesc * previous, BlockDesc * current);
private:
	size_t HSize;
	BlockDesc * FreeList;
	list * AllocList;
	size_t availableMemory;
	void * pMyMem;
	size_t mSize;
	MemoryManager(void * iMem, size_t i_Size);


};

#endif;


