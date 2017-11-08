#include "EngineHeader.h"
#include "InputMove.h"
#include "Random.h"

	using namespace std;
	void main(int i_argc, char ** i_argl)
	{
		Actor	Player(Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f));
		int n = 0;
	bck:
		cout << "Enter amount of monsters (less than 20) :" << endl;
		cin >> n;
		if (n > 20)
		{
			cout << "Monster Limit exceeded pls enter less than 50" << endl;
			goto bck;
		}

		Actor Monster[20];

		InputMove strt;
		Random rnd;
		char ch;
		do
		{
			strt.UpdateActor(&Player);
			for (int i = 0; i < n; i++)
				rnd.UpdateActor(&Monster[i]);
			cout << " Enter 'q' to quit" << endl;
			cin >> ch;
		} while (ch != 'q');

		cin >> n;
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