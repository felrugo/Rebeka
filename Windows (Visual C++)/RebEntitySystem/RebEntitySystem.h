#ifndef REBENTITYSYSTEM_H
#define REBENTITYSYSTEM_H

#include "RebEntity.h"
#include "CompVisual.h"
#include "CompPhysic.h"
#include "CompInput.h"

class RebEntitySystem;

class TemplateManager
{
	std::vector<TEntity*> temps;
	std::vector<TComponent*> ctemps;
	RebEntitySystem * res;
public:
	TemplateManager(RebEntitySystem * sres);

	void AddTamplate(TEntity * toadd);

	void AddCompTemp(TComponent * toadd);

	TEntity * GetTemplate(std::string tname);

	Entity * CreateEntByTemp(std::string entname, std::string tempname);

	void CreateEntTemp(std::string tname, std::vector<TComponent*> tcomps); 

	~TemplateManager();

};



class RebEntitySystem
{
	std::vector<Entity*> ents;
	TemplateManager * tm;
public:
	RebEntitySystem();

	void AddEntity(Entity * ent);
	
	TemplateManager * GetTemplateManager();

	Entity * GetEntity(std::string name);

	void Update();

	void Release();

	~RebEntitySystem();
};


#endif