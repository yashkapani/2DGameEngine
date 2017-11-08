#include "EngineHeader.h"

using namespace std;
int main(int i_argc, char ** i_argl)
{
bck:
	int n = 0;


	int grid1[10][10];
	cout << "Enter amount of monsters (less than 50) :" << endl;
	cin >> n;
	if (n > 50)
	{
		cout << "Monster Limit exceeded pls enter less than 50" << endl;
		goto bck;
	}
	MonsterEngine::EngineSource(n);
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



		MonsterEngine::display(s, n);



	} while (ch != 'q');

	cout << "Thank you for playing Monster Chase 2D" << endl;
	cin >> n;


	return 0;
}
