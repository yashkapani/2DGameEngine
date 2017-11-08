#include "StringPool.h"
#include "NamedBitSet.h"

class UnitTestStrings
{

	void unitTest(){
		Engine::HashedString h11("test");
		Engine::HashedString h21("test");

		MessagedAssert(h11 == h21, "");



		Engine::HashedString h1("test1");
		Engine::HashedString h2("test2");
		Engine::HashedString h3("test1");

		Engine::NamedBitSet<char> NBS;
		unsigned int a = NBS.GetBitIndex(h1);
		unsigned int b = NBS.GetBitIndex(h2);
		unsigned int c = NBS.GetBitIndex(h3);

		MessagedAssert(a == c, "");
		bool res = NBS.FindBitIndex("test2", b);

		MessagedAssert(res, "");




		Engine::StringPool * pTestPool = Engine::StringPool::Create(1024);
		MessagedAssert(pTestPool, "");

		const char * pP1 = pTestPool->find("This");
		const char * pP2 = pTestPool->find("is");
		const char * pP3 = pTestPool->find("a");
		const char * pP4 = pTestPool->find("test");
		const char * pP5 = pTestPool->find("a");

		// pP3 and pP5 should now be the same sharing one string in the string pool
		MessagedAssert(pP5 == pP3, "");

		delete pTestPool;


	}
};
