#ifndef __PROCEES_FILE_H
#define __PROCESS_FILE_H

class Process_File{
public:
	virtual bool ProcessFile(const char *, void *, size_t) = 0;
	
};

#endif 