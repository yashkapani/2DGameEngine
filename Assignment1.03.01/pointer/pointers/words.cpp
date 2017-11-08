#include "Header.h"
using namespace std;

	char *merge(char *words[])
	{
		int count = 0;
		int j = 0;
		int k = 0;
		int i = 0;
		//for (int i = 0; i < 4; i++)
		while (words[i][0] != '\0')
		{
			j = -1;
			do{
				count++;
				j++;
			} while (words[i][j] != '\0');
			i++;
		}
		j = 0;
	
		char *sentence = (char*)malloc(count+1);
		for (i = 0; i < count - 1; i++)
		{
			if (words[j][k] == '\0')
			{
				sentence[i] = ' ';
				k = 0;
				j++;
			}
			else
			{
				sentence[i] = words[j][k];
				k++;
			}

		}
		sentence[i] = '.';
		sentence[i + 1] = '\0';
		return sentence;
	}

int main()
{
	 
	int n = 0;
	
	//cout << "enter the number of words to be entered" << endl;
	//n = 4;
	//char **words = (char**)malloc((n + 1)*sizeof(char*));
	char *words[] = { "This", "is", "a", "test", "" };
	   
		
		cout << "sentemnce is: \t";
			cout << merge(words);
		
		cin >> n;
	
}
