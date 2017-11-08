#include "Header.h"

using namespace std;


int print(int cache[100][100], int nsets, int nlines,int count)
{
	for (int i = 0; i < nsets; i++)
	{
		cout << "SET[" << i << "] :" << endl;
		for (int j = 0; j < nlines; j++)
		{
			if (cache[i][j] == NULL)
				cout << "Line["<<j<<"]empty" << endl;
			else{
				cout << "Line[" << j << "]" << setfill('0') << setw(count)<<std::hex << cache[i][j] << endl;;
			}
		}
		cout << endl;
	}
	return 0;
}
int input(int cache[100][100], int nsets, int nlines,int clwidth,int base,int size,int count)
{

	int newaddr = base + rand()%size;
	int newoffset = newaddr&(clwidth - 1);
	int newset = (newaddr / clwidth)&(nsets - 1);
	int newtag = (newaddr / clwidth)/nsets;


	
	//cout << hex << newtag<<endl;
	//printf("0x%X", newtag);

	//cout << newtag << endl;
	std::cout << "Randomly generated new address is:" << setfill('0') << setw(count) << std::hex << newaddr << endl;
	std::cout << "Tag=" << setfill('0') << setw(count) << std::hex << newtag << endl;
	std::cout << "Set="<<std::hex << newset << endl;
	std::cout << "Offset=" << setfill('0') << setw(count) << std::hex << newoffset << endl;
	//cout <<  newset << endl;
	int i = newset;
	int flag = 0;
	int j;
	for (j = 0; j < nlines; j++)
	{
		if (cache[i][j] == NULL)
		{
			cout << "Not present in cache,  Populating  SET[" << i << "] and Line[" << j << "] for " << setfill('0') << setw(count) << newaddr << endl;
			flag = 1;
			cache[i][j] = newtag;
			break;
		}
		else
		{
			if (cache[i][j] ==  newtag)
			{
				flag = 1;
				cout << "Its a Hit present in SET["<<i<<"] and Line["<<j<<"]" << endl;
				break;
				
			}
		}

				
	}
	 j = rand() % (nlines - 1);

	if (flag == 0)
	{
		j = rand() % (nlines - 1);
		cache[i][j] = newtag;
		cout << "Cache memory full, Stored in new random location SET[" << i << "] and Line[" << j << "] for" << setfill('0') << setw(count) << newaddr << endl;
	}

	return 0;
}
void main()
{
	int clwidth;
	int nsets;
	int nlines;
	char a;
	cout << "Number of bytes in cache line(power of2)" << endl;
	cin >> clwidth;

	cout << "Number of sets in cache (power of2)" << endl;;
	cin >> nsets;

	cout << "number of lines per set(power of2)" << endl;;
	cin >> nlines;

	int csize = clwidth*nsets*nlines;
	cout << "The total size of cache is: " << csize<<endl;
	int cache[100][100];

	for (int i = 0; i < nsets; i++)
	{
		for (int j = 0; j < nlines; j++)
		{
			cache[i][j] = NULL;
		}
	}
	int base;
	int size;
	cout << "Enter the memory space start(base address) in hexadecimal" << endl;
	cin >> hex >> base;
	//cout << base << endl;
	cout << "Enter the size in hexadecimal "<<endl;
	cin >> hex >> size;
	//cout << base << endl;
	int count=0;
	int s = size;
	while (s > 0)
	{
		s = s / 15;
		count++;
	}
	char ch;
	do{
		cout << "Press d to display cache \n Press r to Randomly generate address and perform cache test  \n Press q to exit  " << endl;
		cin >> ch;
	switch(ch)
	{
	case 'd':
		print(cache, nsets, nlines,count);
		break;
	case 'q':
		break;
	case 'r':
		input(cache, nsets, nlines,clwidth,base,size,count);
		break;
	default:
		break;
	}
}while(ch != 'q');
	
	

}
