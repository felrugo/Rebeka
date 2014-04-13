#ifndef REBPARAM_H
#define REBPARAM_H

#include <string>

class RebParam
{
public:
	void* Data;
	std::string Type;

	RebParam()
	{
		Data = 0;
		Type = typeid(Data).name();
	}

	void DeleteData()
	{
		if(Data != 0)
		{
			delete Data;
			Data = 0;
		}
	}
	template <class T>
	 void operator = (T equ)
	 {
		 DeleteData();
		 Data = new T;
		 *(T*)Data = equ;
		 Type = typeid(T).name();
	 }

	 template <class T>
	 operator T ()
	 {
		 T ret;
		 ret = *(T*)Data;
		 return ret;
	 }

	 template <class T>
	 bool operator == (T equ)
	 {
		 if(typeid(T).name() == Type)
		 {
			 if(*(T*)Data == equ)
			 {
				 return true;
			 }
			 return false;
		 }
		 return false;
	 }


	~RebParam()
	{
		DeleteData();
	}
};


#endif