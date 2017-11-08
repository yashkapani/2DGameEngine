#include <conio.h>
#include <stdio.h>
#include <vector>
#include "Lifer.h"

template <class T>
T RandInRange(T i_Min, T i_Max)
{
	return (T)(i_Min + (rand() / ((T)RAND_MAX + 1) * (i_Max - i_Min + 1)));
}

template<>
unsigned int RandInRange<unsigned int>(unsigned int i_Min, unsigned int i_Max)
{
	return (i_Min + (rand()/ ((unsigned int)RAND_MAX+1)) % (i_Max - i_Min + 1));
}

template <>
int RandInRange<int>(int i_Min, int i_Max)
{
	return (i_Min + (rand() % (i_Max - i_Min + 1)));
}

/*struct Lifer
{
	bool			has_procreated;
	int				loc_x;
	int				loc_y;

	unsigned int	lifetime;
	unsigned int	children;
} Lifers[500];
*/
void main( int i_argc, char ** i_argl )
{
	Lifer life[500];

	unsigned int children_created_this_frame;
	unsigned int deaths_this_frame;

	for( unsigned int i = 0; i < 500; i++ )
	{
		life[i].setChild(0);
		life[i].setLife((int) RandInRange(10,30));
		life[i].setx( (int) RandInRange(-100,100));
	    life[i].sety( (int) RandInRange(-100,100));
	}

	unsigned int num_lifers = RandInRange(200,400);
	
	do 
	{
		for ( unsigned int i = 0; i < num_lifers; i++ )
			life[i].setProc(false);
		
		for ( unsigned int i = 0; i < num_lifers; i++ )
		{
			unsigned int distance_to_travel = RandInRange(2,6);

			unsigned int travel_x = RandInRange<unsigned int>(1,distance_to_travel);
			unsigned int travel_y = distance_to_travel - travel_x;

			//Lifers[i].loc_x += travel_x;
			life[i].updatex(travel_x);
			//Lifers[i].loc_x += travel_y;
			life[i].updatey(travel_y);
		}

		// Procreate
		children_created_this_frame = 0;

		for ( unsigned int i = 0; i < num_lifers; i++ )
		{
			for( unsigned int j = i + 1; j < num_lifers; j++)
			{
				if( !life[i].getProc()  &&  !life[j].getProc()  && (life[i].getx() == life[j].getx())  &&  (life[i].gety() == life[j].gety())  &&  (num_lifers < 500))
				{
					// count the children we've created this frame
					children_created_this_frame++;

					// mark that these two have procreated. Lifers can only procreate once per cycle
					//Lifers[i].has_procreated = true;
					life[i].setProc(true);
					//Lifers[j].has_procreated = true;
					life[j].setProc(true);
					// count the children we've created
					//Lifers[i].children++;
					life[i].updateChild(1);
					//Lifers[j].children++;
					life[j].updateChild(1);
					// create a new Lifer
					//Lifers[num_lifers].children = 0;
					life[num_lifers].setChild(0);
					//Lifers[num_lifers].lifetime = (unsigned int) RandInRange(50,100);
					life[num_lifers].setLife((unsigned int) RandInRange(50,100));
					//Lifers[num_lifers].loc_x = (int) RandInRange(-100,100);
					life[num_lifers].setx((int) RandInRange(-100,100));
					//Lifers[num_lifers].loc_y = (int) RandInRange(-100,100);
					life[num_lifers].sety((int) RandInRange(-100,100));
					num_lifers++;
				}
			}
		}

		deaths_this_frame = 0;

		for ( unsigned int i = 0; i < num_lifers; i++ )
		{
			//if( !Lifers[i].has_procreated  && --Lifers[i].lifetime == 0 )
			if(!life[i].getProc() && --life[i].lifetime == 0)
			{
				deaths_this_frame++;
				//Lifers[i] = Lifers[--num_lifers];
				life[i] = life[--num_lifers];
			}
		}

		printf( "Children created this cycle: %d\n", children_created_this_frame );
		printf( "Deaths this cycle: %d\n", deaths_this_frame );
		printf( "Lifers alive: %d\n", num_lifers );
		printf( "\nHit any key to continue\n" );
		_getch();

	} while ( num_lifers );

}