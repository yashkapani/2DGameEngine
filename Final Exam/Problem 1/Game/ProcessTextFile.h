#ifndef __Process_Text_File_H
#define __Process_Text_File_H

#include <stdio.h>

#include "Engine.h"

class TextProcess_File : public Process_File{

public:
	TextProcess_File() {};

	inline bool ProcessFile(const char * i_pFilename, void * i_pFileContents, size_t i_sizeFileContents)
	{
		printf("The contents of %s are:\n", i_pFilename);

		char * pChars = reinterpret_cast<char *>(i_pFileContents);

		while (i_sizeFileContents--)
			putchar(*pChars++);

		return true;
	};

	~TextProcess_File() {};
};

#endif