#include "EngineHeader.h"

namespace MonsterEngine
{
	int i;
	int j;
	int monster[50][2];
	int grid[10][10];
	int playerx = 0;
	int playery = 0;
	using namespace std;
	int EngineSource(int n)
	{



		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				grid[i][j] = 0;
			}
		}
		//cout << "number of monster is n:" <<n<< endl;
		//cin >> n;
		for (i = 0; i < n; i++)
		{
			monster[i][0] = (rand() % 10);
			monster[i][1] = (rand() % 10);
			cout << "Monster Number " << (i + 1) << "is at location [" << monster[i][0] << "][" << monster[i][1] << "]" << endl;
			grid[monster[i][0]][monster[i][1]] = (i + 1);

		}

		cout << "You are at location [" << playerx << "][" << playery << "]" << endl;
		grid[playerx][playery] = 99;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (grid[i][j] == 0)
					cout << "| |";
				else
				{
					if (grid[i][j] == 99)
						cout << "|P|";
					else
						cout << "|" << grid[i][j] << "|";
				}
			}
			cout << endl;
		}
		return 0;
	}

	




	int down()
	{
		grid[playerx][playery] = 0;
		playerx = (playerx + 1) % 10;
		grid[playerx][playery] = 99;
		return 0;
	}

	int up()
	{
		grid[playerx][playery] = 0;
		if (playerx == 0)
			playerx = 9;
		else
			playerx = playerx - 1;
		grid[playerx][playery] = 99;
		return 0;
	}
	int right()
	{
		grid[playerx][playery] = 0;
		playery = (playery + 1) % 10;
		grid[playerx][playery] = 99;
		return 0;
	}
	int left()
	{
		grid[playerx][playery] = 0;
		if (playery == 0)
			playery = 9;
		else
			playery = playery - 1;
		grid[playerx][playery] = 99;
		return 0;
	}
	int display(char ch, int n)
	{
		if (ch != 'q')
		{
			for (i = 0; i < n; i++)
			{
				grid[monster[i][0]][monster[i][1]] = 0;
				monster[i][0] = (rand() % 10);
				monster[i][1] = (rand() % 10);
				cout << "Monster Number " << (i + 1) << "is at location [" << monster[i][0] << "][" << monster[i][1] << "]" << endl;
				grid[monster[i][0]][monster[i][1]] = (i + 1);
			}

			cout << "You are at location [" << playerx << "][" << playery << "]" << endl << endl;

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (grid[i][j] == 0)
						cout << "| |";
					else
					{
						if (grid[i][j] == 99)
							cout << "|P|";
						else
							cout << "|" << grid[i][j] << "|";
					}
				}
				cout << endl;
			}

		}
		return 0;

	}

}