#include "RebFileSystem.h"


RebFileSystem::RebFileSystem()
{
	Files.clear();
}



std::string GetType(std::string filename)
{
	if(filename.size() < 3)
		return "unknow";
	std::size_t f;
	f = filename.rfind(".");
	std::string ret = filename.substr(f, filename.size() - f);
	return ret;
}

#ifdef _WIN32

bool isDir(std::string fname)
{
	if(fname.find(".") == std::string::npos)
	{
		return true;
	}
	return false;
}

std::string GetPath(std::string relativedir, std::string filename)
{
	std::size_t f = 0;
	UINT up = 0;
	TCHAR asd[256];
	GetCurrentDirectory(256, asd);
	while(relativedir.find("..", f) != std::string::npos)
	{
		up++;
		f = relativedir.find("..", f) + 2;
	}
	std::string absdir = asd;

	for (unsigned int i = 0; i < up; i++)
	{
		f = absdir.rfind("\\");
		if(f == std::string::npos)
		{
			return relativedir + "\\" + filename;
		}
		absdir.erase(absdir.begin() + f, absdir.end());
	}
	return absdir + "\\" + filename;
}

void RebFileSystem::GetAllFiles(std::string dir)
{
WIN32_FIND_DATA search_data , sd2;

std::string ret;
   memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
   memset(&sd2, 0, sizeof(WIN32_FIND_DATA));

   HANDLE nomedia = FindFirstFile((dir + "\\.nomedia").c_str(), &search_data);

   if (nomedia != INVALID_HANDLE_VALUE)
   {
	   return;
   }

   HANDLE handle = FindFirstFile((dir + "\\*").c_str(), &search_data);
   
   while(handle != INVALID_HANDLE_VALUE)
   {
	  ret = search_data.cFileName;

	  if(isDir(ret))
	  {
		  GetAllFiles(dir + "\\" + ret);
	  }
	  else{
	  RebFile rf;
	  rf.fname = ret;
	  rf.path = GetPath(dir, ret);
	  rf.type = GetType(ret);
	  Files.push_back(rf);
	  }
      if(FindNextFile(handle, &search_data) == FALSE)
        break;
   }

   //Close the handle after use or memory/resource leak
   FindClose(handle);
    }

#elif __linux__
#endif

