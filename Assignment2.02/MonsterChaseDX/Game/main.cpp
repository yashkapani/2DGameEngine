



#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
/*
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif*/
#endif 

//#include "EngineHeader.h"
//#include "InputMove.h"
//#include "Random.h"
//#include "MemoryManager.h"
#include "NamedBitSet.h"
#include "StringPool.h"
#include "HashedString.h"
#include "../../MonsterEngine/HashedString.h"
#include <Windows.h>
#include <stdio.h>
#include <Cheesy.h>
#include <Sprite.h>
#include <Texture.h>
#include <Text.h>
#include <assert.h>
#include <crtdbg.h>
#include <stdlib.h>
#include "Update.h"
#include "SharedPtr.h"
#include "Timing.h"
#include "Game.h"
#include "Renderer.h"
#include "AutoPtr.h"
#include "Matrix.h"



//MemoryManager* MemMan = NULL;

//inline void* operator new(size_t i_size){
//	if (MemMan == NULL)
//	{
//		MemMan = MemoryManager::newMemory(1024 * 1024);
//	}
//	return MemMan->alloc(i_size);
//}
//
//inline void operator delete(void* i_ptr){
//	if (MemMan == NULL || i_ptr == NULL)
//	{
//		return;
//	}
//	MemMan->_free(i_ptr);
//}

int oldmain();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// This call creates the windows, initializes DirectX and Cheesy
	
	Timing::tick start, end;
	float dt = 1.0f / 60.0f;
	LuaPlus::LuaState* pState = LuaPlus::LuaState::Create();
	char * luaFile = "Data\\ActorsToCreate.lua";
	//Game::initGame();
	Cheesy::Create("Cheesy Test App", 640, 480, false, false);
	Game::initGame(pState, luaFile);
	while (true){
		
		start = Timing::GetCurrentTickCounter();
		Game::updateGame(dt);
		Engine::Renderer::draw();
		end = Timing::GetCurrentTickCounter();
		dt = Timing::GetTimeDiff_ms(start, end);
	}

	/*AllocConsole();
	freopen("CONIN$", "rb", stdin);   // reopen stdin handle as console window input
	freopen("CONOUT$", "wb", stdout);  // reopen stout handle as console window output

	oldmain();

	FreeConsole();*/

}

/*
int oldmain()
{
	void testfloating();

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
void testfloating()
{
	//testing isNAN function
	cout << "testing isNAN function" << endl;
	float testNumber = NAN;
	cout << FloatingPoint::IsNaN(testNumber) << endl;
	testNumber = INFINITY;
	cout << FloatingPoint::IsNaN(testNumber) << endl;
	testNumber = -0.0f;
	cout << FloatingPoint::IsNaN(testNumber) << endl;
	testNumber = 0.0f;
	cout << FloatingPoint::IsNaN(testNumber) << endl << endl;

	//testing isInfinity function
	cout << "testing isInfinity function" << endl;
	testNumber = NAN;
	cout << FloatingPoint::IsInfinity(testNumber) << endl;
	testNumber = INFINITY;
	cout << FloatingPoint::IsInfinity(testNumber) << endl;
	testNumber = -0.0f;
	cout << FloatingPoint::IsInfinity(testNumber) << endl;
	testNumber = 0.0f;
	cout << FloatingPoint::IsInfinity(testNumber) << endl << endl;

	//testing CheckEqual function
	cout << "testing CheckEqual function" << endl;
	float testNumber1 = -0.0;
	float testNumber2 = 0.0f;
	cout << FloatingPoint::CheckFloatEqualWithULPS(testNumber1, testNumber2, 1) << endl;
	testNumber1 = -0.0000001f;
	testNumber2 = 0.0f;
	cout << FloatingPoint::CheckFloatEqualWithULPS(testNumber1, testNumber2, 1) << endl;
	testNumber1 = 0.0000001f;
	testNumber2 = 0.0f;
	cout << FloatingPoint::CheckFloatEqualWithULPS(testNumber1, testNumber2, 1) << endl;
	testNumber1 = 0.0f;
	testNumber2 = 0.0f;
	cout << FloatingPoint::CheckFloatEqualWithULPS(testNumber1, testNumber2, 1) << endl;
	testNumber1 = 1.0000001f;
	testNumber2 = 1.0000001f;
	cout << FloatingPoint::CheckFloatEqualWithULPS(testNumber1, testNumber2, 1) << endl << endl;


}
*/

void unitTest(){
	Engine::StringPool * pTestPool = Engine::StringPool::Create(1024);
	MessagedAssert(pTestPool, "");

	const char * pP1 = pTestPool->find("This");
	const char * pP2 = pTestPool->find("is");
	const char * pP3 = pTestPool->find("a");
	const char * pP4 = pTestPool->find("test");
	const char * pP5 = pTestPool->find("a");
	const char * pP6 = "This";
	Engine::HashedString h1 = pP1;
	Engine::HashedString h2 = pP6;

	Engine::NamedBitSet<unsigned int> namedBitSet1;
	uint32_t states;
	states |= namedBitSet1.GetBitMask("isCrazy");
	states |= namedBitSet1.GetBitMask("isHuman");

	MessagedAssert(states & namedBitSet1.GetBitMask("isCrazy"), "NamedBitSet failed")
		// pP1 & pP5 should now be hashed to the same value and be comparable.
		MessagedAssert(h1 == h2, "HashedStirng failed");

	// pP3 and pP5 should now be the same sharing one string in the string pool
	MessagedAssert(pP5 == pP3, "Stringpool failed");

	delete pTestPool;

	Matrix Mat1 = Matrix(1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4,
		4, 5, 6, 7);
	Matrix Mat2 = Matrix(1, 2, 3, 4,
		5, 6, 7, 8,
		1, 2, 3, 4,
		4, 5, 6, 7);

	Vector4 Vec41 = Vector4(5, 6, 7, 8);
	Vector4 Vec42 = Mat1*Vec41;
	Vector4 Vec43 = Vector4(70, 70, 70, 148);
	MessagedAssert(Vec42 == Vec43, "Matrix * Vector 4 failed");
	Mat1.SetToIdentity();
	Matrix identity = Matrix(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	MessagedAssert(Mat1 == identity, "SetToIdentity failed");
	Mat1.SetToScale(3, 4, 1);
	MessagedAssert(Mat1 == Matrix(3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), "Set to Scale failed");
	Mat1 = Matrix(1, 2, 3, 4,
		1, 2, 3, 4,
		1, 2, 3, 4,
		4, 5, 6, 7);
	Matrix Mat3 = Mat1 * Mat2;
	MessagedAssert(Mat3 == Matrix(30, 40, 50, 60, 30, 40, 50, 60, 30, 40, 50, 60, 63, 85, 107, 129), "Matrix Multiplication failed");
	Mat3 = Matrix(4, 0, 0, 0,
		0, 0, 2, 0,
		0, 1, 2, 0,
		1, 0, 0, 1);
	Mat3.Invert();
	MessagedAssert(Mat3 == Matrix(0.25, 0, 0, 0, 0, -1, 1, 0, 0, 0.5, 0, 0, -0.25, 0, 0, 1), "Invert failed");

	Mat1.Transpose();
	MessagedAssert(Mat1 == Matrix(1, 1, 1, 4, 2, 2, 2, 5, 3, 3, 3, 6, 4, 4, 4, 7), "Transpose failed");

	Mat1.SetToXRotation(90);
	Mat2.Transpose();

}
/*
void UnitTest()
{
	
	void unitTest(){
		Engine::StringPool * pTestPool = Engine::StringPool::Create(1024);
		MessagedAssert(pTestPool, "");

		const char * pP1 = pTestPool->find("This");
		const char * pP2 = pTestPool->find("is");
		const char * pP3 = pTestPool->find("a");
		const char * pP4 = pTestPool->find("test");
		const char * pP5 = pTestPool->find("a");
		const char * pP6 = "This";
		Engine::HashedString h1 = pP1;
		Engine::HashedString h2 = pP6;

		Engine::NamedBitSet<unsigned int> namedBitSet1;
		uint32_t states;
		states |= namedBitSet1.GetBitMask("isCrazy");
		states |= namedBitSet1.GetBitMask("isHuman");

		MessagedAssert(states & namedBitSet1.GetBitMask("isCrazy"), "NamedBitSet failed")
			// pP1 & pP5 should now be hashed to the same value and be comparable.
			MessagedAssert(h1 == h2, "HashedStirng failed");

		// pP3 and pP5 should now be the same sharing one string in the string pool
		MessagedAssert(pP5 == pP3, "Stringpool failed");

		delete pTestPool;

		Matrix Mat1 = Matrix(1, 2, 3, 4,
			1, 2, 3, 4,
			1, 2, 3, 4,
			4, 5, 6, 7);
		Matrix Mat2 = Matrix(1, 2, 3, 4,
			5, 6, 7, 8,
			1, 2, 3, 4,
			4, 5, 6, 7);

		Vector4 Vec41 = Vector4(5, 6, 7, 8);
		Vector4 Vec42 = Mat1*Vec41;
		Vector4 Vec43 = Vector4(70, 70, 70, 148);
		MessagedAssert(Vec42 == Vec43, "Matrix * Vector 4 failed");
		Mat1.SetToIdentity();
		Matrix identity = Matrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		MessagedAssert(Mat1 == identity, "SetToIdentity failed");
		Mat1.SetToScale(3, 4, 1);
		MessagedAssert(Mat1 == Matrix(3, 0, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1), "Set to Scale failed");
		Mat1 = Matrix(1, 2, 3, 4,
			1, 2, 3, 4,
			1, 2, 3, 4,
			4, 5, 6, 7);
		Matrix Mat3 = Mat1 * Mat2;
		MessagedAssert(Mat3 == Matrix(30, 40, 50, 60, 30, 40, 50, 60, 30, 40, 50, 60, 63, 85, 107, 129), "Matrix Multiplication failed");
		Mat3 = Matrix(4, 0, 0, 0,
			0, 0, 2, 0,
			0, 1, 2, 0,
			1, 0, 0, 1);
		Mat3.Invert();
		MessagedAssert(Mat3 == Matrix(0.25, 0, 0, 0, 0, -1, 1, 0, 0, 0.5, 0, 0, -0.25, 0, 0, 1), "Invert failed");

		Mat1.Transpose();
		MessagedAssert(Mat1 == Matrix(1, 1, 1, 4, 2, 2, 2, 5, 3, 3, 3, 6, 4, 4, 4, 7), "Transpose failed");

		Mat1.SetToXRotation(90);
		Mat2.Transpose();

	}
	/*
	Engine::HashedString h1("test");
	Engine::HashedString h2("test");

	assert(h1 == h2);
	

	
		Engine::HashedString h1("test1");
		Engine::HashedString h2("test2");
	  Engine::HashedString h3("test1");

		Engine::NamedBitSet<char> NBS;
		unsigned int a = NBS.GetBitIndex(h1);
		unsigned int b = NBS.GetBitIndex(h2);
		unsigned int c = NBS.GetBitIndex(h3);

		assert(a == c);
		bool res = NBS.FindBitIndex("test2", b);

		assert(res);

	
	
	
		Engine::StringPool * pTestPool = Engine::StringPool::Create(1024);
		assert(pTestPool);

		const char * pP1 = pTestPool->find("This");
		const char * pP2 = pTestPool->find("is");
		const char * pP3 = pTestPool->find("a");
		const char * pP4 = pTestPool->find("test");
		const char * pP5 = pTestPool->find("a");

		// pP3 and pP5 should now be the same sharing one string in the string pool
		assert(pP5 == pP3);

		delete pTestPool; 
		
		

		}*/