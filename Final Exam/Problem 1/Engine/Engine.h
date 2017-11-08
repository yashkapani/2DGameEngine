#ifndef __Engine_H
#define __Engine_H

#include <stdio.h>
#include <io.h>

#include <algorithm>
#include <map>
#include <string>
#include <cassert>

#include "Process_File.h"

class Engine
{
	
private:
	typedef std::map<std::string, Process_File *> FileLoaderContainer;
	FileLoaderContainer	m_FileLoaders;

private:
	bool ReadFileContents(const char * i_pFilename, void * & o_pFileContents, size_t & o_sizeFileContents);

public:
	Engine() {};
	void ProcessDataDirectory(std::string i_path);
	void AddFileLoader(const char * i_pFileExt, Process_File *i_Process_File);

};

#endif 