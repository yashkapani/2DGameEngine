
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif  

#include "stdlib.h"
#include "Math/Vector3.h"

#include <vector>
#include <algorithm>

float RandInRange( float i_Min, float i_Max)
{
	return i_Min + (static_cast<float>( rand() ) / (RAND_MAX + 1) * (i_Max - i_Min + 1));
}

Engine::Vector3 GenerateRandomVector( const Engine::Vector3 & i_Min, const Engine::Vector3 & i_Max)
{
	return Engine::Vector3( 
		RandInRange( i_Min.x(), i_Max.x() ),
		RandInRange( i_Min.y(), i_Max.y() ),
		RandInRange( i_Min.z(), i_Max.z() ) );
}


class WayPoint
{
public:

	WayPoint( const char * i_pName, unsigned int i_Quality, const Engine::Vector3 & i_Location );

	Engine::Vector3 getLocation() const { return m_Location; }
	const char * getName() const { return m_pName; }
	unsigned int getQuality() const { return m_Quality;}
	static Engine::Vector3 getMyLoc() { return m_Myloc; }
	static void SetMyloc(Engine::Vector3 &i_Myloc) {m_Myloc=i_Myloc;}

private:
	const char *	m_pName;
	unsigned int	m_Quality;
	Engine::Vector3	m_Location;
	static Engine::Vector3	m_Myloc;
	//
} ;

Engine::Vector3 WayPoint::m_Myloc(0.0f, 0.0f, 0.0f);
WayPoint::WayPoint( const char * i_pName, unsigned int i_Quality, const Engine::Vector3 & i_Location ) :
	m_pName( i_pName ),
	m_Quality( i_Quality ),
	m_Location( i_Location )
{

}

/* Your Job:
	Make sure this program works properly and exits cleanly, leaking no memory. You may add what you need to
	to the WayPoint class.
*/
bool Qualitysort(WayPoint a, WayPoint b)
{
	Engine::Vector3 l = WayPoint::getMyLoc();
	Engine::Vector3 x = a.getLocation();
	Engine::Vector3 y = a.getLocation();
	if(a.getQuality()==b.getQuality())
	{
		float v1= (l.x()-x.x())*(l.y()-x.y())*(l.z()-x.z());
		float v2= (l.x()-y.x())*(l.y()-y.y())*(l.z()-y.z());
		//return (WayPoint::getMyLoc()-a.getLocation()< WayPoint::getMyLoc()-b.getLocation());
		return (unsigned int)v1<(unsigned int)v2;
	}
	return a.getQuality()>b.getQuality();
};

void main( int i_Argc, char ** i_pArgl )
{
	float Min= -1000.0f, Max = 1000.0f,  MaxQuality = 10, MinQuality = 0;
	unsigned int MaxWayPoints = 10;
	std::vector<WayPoint> * SafeLocations = new std::vector<WayPoint>;

	Engine::Vector3	MinDistance( Min, Min, 0.0f );
	Engine::Vector3	MaxDistance(  Max,  Max, 0.0f );
	
	unsigned int LocationNumber = 0;

	for( unsigned int i = 0; i < MaxWayPoints; i++)
	{
		char name[16];
		sprintf_s( name, "Location #%d", LocationNumber++ );
		SafeLocations->push_back( WayPoint( name, (unsigned int)RandInRange( MinQuality, MaxQuality ), GenerateRandomVector( MinDistance, MaxDistance ) ) );
	}
	printf("Before Sorting");
	for( unsigned int i = 0; i < MaxWayPoints; i++ )
	{
		
		printf(" \n Going to %s Quality:%d Location:( x:[%d],y:[ %d], z:[%d] )\n", SafeLocations->at(i).getName(), SafeLocations->at(i).getQuality(), SafeLocations->at(i).getLocation().x(), SafeLocations->at(i).getLocation().y(), SafeLocations->at(i).getLocation().z());
	}

	//for( unsigned int i = 0; i < MaxWayPoints; i++)
	//{
		Engine::Vector3	MyLocation = GenerateRandomVector( MinDistance, MaxDistance );
		WayPoint::SetMyloc(MyLocation);
		/* Your Job: 
			Sort SafeLocations so the vector is arranged first by Quality (higher is better), then closest to MyLocation to farthest from MyLocation,
			using std::sort() and a function object (i.e. functor) of your design.
			So the closest Quality 10, followed by the second closest Quality 10, until there are no more Quality 10, then closest Quality 9, etc.

		*/
		std::sort(SafeLocations->begin(), SafeLocations->end(),Qualitysort);
		

		/* Your Job:
			Remove the closest WayPoint from the list and add a new WayPoint
		*/
	printf("After Sorting");
		for( unsigned int i = 0; i < MaxWayPoints; i++ )
	{
	
			printf(" \n Going to %s Quality:%d Location:( x:[%d],y:[ %d], z:[%d] )\n", SafeLocations->at(i).getName(), SafeLocations->at(i).getQuality(), SafeLocations->at(i).getLocation().x(), SafeLocations->at(i).getLocation().y(), SafeLocations->at(i).getLocation().z());
}
		SafeLocations->erase(SafeLocations->begin());
		char name[16];
		sprintf_s( name, "Location #%d", LocationNumber++ );
		SafeLocations->push_back( WayPoint( name, (unsigned int)RandInRange( MaxQuality, MinQuality ), GenerateRandomVector( MinDistance, MaxDistance ) ) );
	
	//was not sure dowe have to print all of them before sorting or just the closest.
	printf("After Adding New Node");
		for( unsigned int i = 0; i < MaxWayPoints; i++ )
{
	
			printf(" \n Going to %s Quality:%d Location:( x:[%d],y:[ %d], z:[%d] )\n", SafeLocations->at(i).getName(), SafeLocations->at(i).getQuality(), SafeLocations->at(i).getLocation().x(), SafeLocations->at(i).getLocation().y(), SafeLocations->at(i).getLocation().z());
}
	//}
		
		delete SafeLocations;
		
#ifdef _DEBUG
		_CrtDumpMemoryLeaks();
#endif  
	getchar();
}
