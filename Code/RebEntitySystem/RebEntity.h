#ifndef REBENTITY_H
#define REBENTITY_H

#include <vector>
#include <string>
#include <map>
#include <typeinfo>
#include "..\RebSupport\RebString.h"
#include "..\RebRenderer\IRenderDevice.h"
#include "..\RebWindowSystem\IMEH.h"
#include "..\RebSupport\RebParam.h"


class Entity;

class TemplateManager;

class Component
{
protected:
	Entity * parent;

	std::map<std::string, RebParam> Params;
public:
	virtual std::string GetType() = 0;

	Component() : parent(0) {};

	virtual std::string GetID()
	{
		return "BaseComponent";
	}

	virtual void update() {}

	void AddParams(std::map<std::string, RebParam> spars)
	{

		for(std::map<std::string, RebParam>::iterator it = spars.begin(); it != spars.end(); it++) {
			Params[it->first] = it->second;
		}
	}

	template <class T>
	void SetParam(std::string paramname, T paramvalue)
	{
		Params[paramname] = paramvalue;
	}

	RebParam GetParam(std::string paramname)
	{
		for(std::map<std::string, RebParam>::iterator it = Params.begin(); it != Params.end(); it++) {
			if(it->first == paramname)
			{
				return Params[paramname];
			}
		}
	}

	void SetOwner(Entity * so)
	{
		parent = so;
	}

	Entity * GetOwner()
	{
		return parent;
	}

	virtual ~Component() {}
};

class TComponent
{
public:

	std::map<std::string, RebParam> TParams;

	TComponent() {};
	virtual ~TComponent() {};

	virtual std::string GetID() = 0;


	virtual std::string GetType() = 0;

	virtual Component * MakeComponent() = 0;
};




class TEntity
{
	protected:
	std::string name;
	std::vector<TComponent*> temps;
	TEntity(std::string sname);
public:
	~TEntity();

	void SetName(std::string ID);

	std::string GetName();

	TComponent * GetTemplate(std::string ID);

	std::vector<TComponent*> * GetTComps();

	void AddTemplate(TComponent * atemp);

	void Clear();

	friend class TemplateManager;
};


class Entity
{
protected:
	RebVector pos;
	RebVector ori;
	std::string name;
	std::vector<Component*> comps;
public:
	Entity(std::string ID);

	void SetID(std::string ID);

	std::string GetID();

	Component * GetComponent(std::string ID);

	Component * SetComponent(Component * scomp);

	void UpdateAllComps();

	void ClearComps();

	RebVector GetPos();

	RebVector GetOri();

	void SetPos(RebVector spos);

	void SetOri(RebVector sori);

	~Entity();
};


#endif