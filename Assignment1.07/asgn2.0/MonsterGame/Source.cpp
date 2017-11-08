#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif 

#include "EngineHeader.h"
#include "InputMove.h"
#include "Random.h"
#include "SmallBlockAllocator.h"

using namespace std;
int main(int i_argc, char ** i_argl)
{
	SmallBlockAllocator * pNewAllocator = SmallBlockAllocator::create(8, 1024);
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
		cout << "Press\n 1: To Create a New Monster \n 2: To Delete a Monster \n 3: Small Block Unit test Any other key to skip" << endl;
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
#ifdef _DEBUG
		else if (opt == '3')
		{

			for (int i = 0; i < 100; i++)
			{

				Actor * x = new Actor(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f), "Monster");
				if (x == NULL)
				{
					cout << "Memory Full"<<endl;
				}
			}
		}
#endif
		//}
		cout << " Enter 'q' to quit" << endl;
		cin >> ch;





	} while (ch != 'q');

	delete Player;
	delete pNewAllocator;
	for (int i = 1; i < no; i++)
		delete NewMonster[i];
	for (int i = 0; i < n; i++)
		delete Monster[i];
	delete strt;
	delete rnd;
	_CrtDumpMemoryLeaks();

	return 0;
}



/*int main(int i_argc, char ** i_argl)
{
bck:
int n = 0;


cout << "Enter amount of monsters (less than 50) :" << endl;
cin >> n;
if (n > 50)
{
cout << "Monster Limit exceeded pls enter less than 50" << endl;
goto bck;
}
MonsterEngine::Player();
MonsterEngine::Monster(n);

char ch;
do
{
c2:
cout << "Enter your next move \n 'r' to move Right \n 'l'to move left \n 'u' to move up \n 'd' to move down \n 'q' to exit " << endl;
cin >> ch;
switch (ch)
{
case 'd':
MonsterEngine::down();
break;
case 'u':
MonsterEngine::up();
break;
case 'r':
MonsterEngine::right();
break;
case 'l':
MonsterEngine::left();
break;
case 'q':
break;
default:
cout << "wrong input pls enter from the below options" << endl;
goto c2;
break;

}
char s = ch;

int update();

MonsterEngine::Monster(n);



} while (ch != 'q');

cout << "Thank you for playing Monster Chase 2D" << endl;
cin >> n;


return 0;
}
*/