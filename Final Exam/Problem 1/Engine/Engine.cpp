#include "Engine.h"

bool Engine::ReadFileContents(const char * i_pFilename, void * & o_pFileContents, size_t & o_sizeFileContents)
{
	FILE * pFile = NULL;

	errno_t error = fopen_s(&pFile, i_pFilename, "rb");

	assert(pFile != NULL);

	if (error == 0 && pFile)
	{
		int result = 0;

		// seek to the end of the file
		result = fseek(pFile, 0, SEEK_END);
		if (result != 0)
		{
			fclose(pFile);
			return false;
		}

		// ftell() now gives us the file size
		o_sizeFileContents = ftell(pFile);
		if (o_sizeFileContents == 0)
		{
			fclose(pFile);
			return false;
		}

		result = fseek(pFile, 0, SEEK_SET);
		if (result != 0)
		{
			fclose(pFile);
			return false;
		}

		// allocate enough memory to hold the file
		o_pFileContents = new char[o_sizeFileContents];
		if (o_pFileContents == NULL)
		{
			fclose(pFile);
			return false;
		}

		// read the file into the buffer
		size_t readLength = fread(o_pFileContents, 1, o_sizeFileContents, pFile);
		if (readLength != o_sizeFileContents)
		{
			delete[] o_pFileContents;
			o_pFileContents = NULL;

			o_sizeFileContents = 0;

			fclose(pFile);
			return false;
		}

		fclose(pFile);

		return true;
	}

	return false;
}

void Engine::ProcessDataDirectory(std::string i_path)
{
	assert(!i_path.empty());

	struct _finddata_t	filedata;
	intptr_t			filehandle;

	filehandle = _findfirst((i_path + "*.*").c_str(), &filedata);

	std::string root(i_path);

	if (filehandle != intptr_t(-1))
	{
		do
		{
			std::string filename(filedata.name);

			std::string::size_type idx = filename.rfind('.');
			if (idx != std::string::npos)
			{
				std::string ext = filename.substr(idx + 1);
				std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

				FileLoaderContainer::iterator iter = m_FileLoaders.find(ext);

				if (iter != m_FileLoaders.end())
				{
					std::string path = root + filename;

					void * pFileContents = NULL;
					size_t sizeFileContents = 0;

					if (ReadFileContents(path.c_str(), pFileContents, sizeFileContents))
					{
						// call our callback
						iter->second->ProcessFile(path.c_str(), pFileContents, sizeFileContents);

						delete[] pFileContents;
					}
				}
			}

		} while (_findnext(filehandle, &filedata) == 0);

		_findclose(filehandle);
	}
}

void Engine::AddFileLoader(const char * i_pFileExt, Process_File *i_Process_File)
{
	assert(i_pFileExt != NULL);

	std::string ext(i_pFileExt);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	// if we pass NULL as the callback unregister this file extension
	if (i_Process_File == NULL)
	{
		m_FileLoaders.erase(m_FileLoaders.find(ext));
	}
	else
	{
		m_FileLoaders[ext] = i_Process_File;
	}
}