#ifndef REBENTITY_H
#define REBENTITY_H

#include <vector>
#include <string>
#include "..\RebRenderer\IRenderDevice.h"
#include "..\RebWindowSystem\IMEH.h"


class Entity;

class TemplateManager;

class Component
{
protected:
	Entity * parent;
public:
	virtual std::string GetType() = 0;

	Component() : parent(0) {};

	virtual std::string GetID()
	{
		return "BaseComponent";
	}

	virtual void update() {}

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