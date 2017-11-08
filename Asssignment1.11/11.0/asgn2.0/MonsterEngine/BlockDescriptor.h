#pragma once
class BlockDescriptor
{
private:
	void * BlockAddress;
	int Empty;
	int NextFree;
	
	int index;

public:

	int size;

	BlockDescriptor();
	BlockDescriptor(void* i_BlockAddress, bool b) : BlockAddress(i_BlockAddress), Empty(b){};

	void setTotalEmpty(int i_empty){ Empty = i_empty; };
	int getTotalEmpty(){ return Empty; };

	void setNextFree(int i_nfree){ NextFree = i_nfree; };
	int getNextFree(){ return NextFree; };

	void setAddress(void* i_BAddress){ BlockAddress = i_BAddress; };
	void* getAddress(){ return BlockAddress; };

	~BlockDescriptor();
};





























