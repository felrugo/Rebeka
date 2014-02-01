#ifndef REBFILESYSTEM_H
#define REBFILESYSTEM_H

#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#endif


struct RebFile
{
public:
	std::string fname;
	std::string path;
	std::string type;
};


class RebFileSystem
{
	std::vector<RebFile> Files;
public:
	RebFileSystem();

	void CreateDirSystem();

	void CreateDir(std::string dirname, std::string path);

	std::string Search(std::string filename);

	void GetAllFiles(std::string dir = "\\");

	std::vector<std::string> Read(std::string path);

	void Write(std::vector<std::string> writable);
};




#endif