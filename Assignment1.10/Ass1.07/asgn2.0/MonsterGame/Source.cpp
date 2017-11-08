#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
/*
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif*/
#endif 

#include "EngineHeader.h"
#include "InputMove.h"
#include "Random.h"
#include "MemoryManager.h"

MemoryManager * Mymem;
using namespace std;
inline void* operator new(size_t i_size){
	///if (MemMan == NULL)
	//{
		//MemMan = MemoryManager::newMemory(1024 * 1024);
	//}
	return Mymem->alloc(i_size);
}

inline void operator delete(void* i_ptr){
	//if (MemMan == NULL || i_ptr == NULL)
	//{
	//	return;
	Mymem->_free(i_ptr);
}

int main(int i_argc, char ** i_argl)
{
	size_t sizeHeap = 1024 * 1024;
	
	Mymem = MemoryManager::create(sizeHeap);

	cout << "hi";
	//SmallBlockAllocator * pNewAllocator = SmallBlockAllocator::create(8, 1024);
	Actor * Player;
	Player = new Actor(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f), "Player");
	//Actor	Player(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f));
	int n = 20;
bck:
	cout << "Enter amount of minumum monsters in game (less than 20) :" << endl;
	cin >> n;
	if (n > 20)
	{
		cout << "Monster Limit exceeded pls enter less than 50" << endl;
		goto bck;
	}
	int no = 0;
	//Actor * n2;
	//n2 = new Actor[n];
	Actor * Monster[20];
	Actor * NewMonster[20];
	for (int i = 0; i < n; i++)
		Monster[i] = new Actor(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f), "Monster");
	IActorController * strt = new InputMove();
	IActorController * rnd = new Random();
	char ch;
	do
	{
		strt->UpdateActor(Player);
		for (int i = 0; i < n; i++)
		{
			cout << " Location of Monster [" << (i + 1) << "]";
			rnd->UpdateActor(Monster[i]);
		}
		for (int i = 0; i < no; i++)
		{
			cout << " Location of Monster [" << (n + (i + 1)) << "]";
			rnd->UpdateActor(NewMonster[i]);
		}
		cout << "Press\n 1: To Create a New Monster \n 2: To Delete a Monster \n Any other key to skip" << endl;
		char opt;
		cin >> opt;
		if (opt == '1')
		{

			if (no > 20)
			{

				cout << "Monster Lmit exceeded" << endl;
			}
			else
			{
				NewMonster[no] = new Actor(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f), "Monster");
				cout << " Location of Monster [" << no + (n + 1) << "]";
				rnd->UpdateActor(NewMonster[no]);
				no++;
			}
		}
		else if (opt == '2')
		{

			if (no>1)
			{
				no--;
				cout << "Monster" << no + (n + 1) << " Deleted" << endl;
				delete NewMonster[no];


			}
			else
			{
				cout << "Minimum  Monsters Required Create new Monsters first to delete" << endl;


			}
		}
		//}
		cout << " Enter 'q' to quit" << endl;
		cin >> ch;





	} while (ch != 'q');

	delete Player;
	//delete pNewAllocator;
	for (int i = 1; i < no; i++)
		delete NewMonster[i];
	for (int i = 0; i < n; i++)
		delete Monster[i];
	delete strt;
	delete rnd;
	_CrtDumpMemoryLeaks();

	return 0;
}



