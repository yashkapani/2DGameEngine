#include <map>
#include <string>

#include "ProcessTextFile.h"
#include "Engine.h"

void main(int i_argc, char ** i_pargs)
{
	using namespace std;
	string path = "..\\data\\";
	
	TextProcess_File *fileobj = new TextProcess_File();
	Engine *dirobj = new Engine();
	dirobj->AddFileLoader("txt", fileobj);
	dirobj->ProcessDataDirectory(path);
	getchar();
}