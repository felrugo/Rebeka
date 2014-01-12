#include "RebEntitySystem.h"



void TemplateManager::AddTamplate(TEntity * toadd)
{
	temps.push_back(toadd);
}

TEntity * TemplateManager::GetTemplate(std::string tname)
{
	for (unsigned int i = 0; i < temps.size(); i++)
		{
			if(temps[i]->GetName() == tname)
			{
				return temps[i];
			}
		}
		return 0;
}

Entity * TemplateManager::CreateEntByTemp(std::string entname, std::string tempname)
{
	Entity * ret = new Entity(entname);
	TEntity * te = GetTemplate(tempname);
	if (te == 0)
	{
		return 0;
	}
	for (unsigned int i = 0; i < te->GetTComps()->size(); i++)
	{
		ret->SetComponent(te->GetTComps()->at(i)->MakeComponent());
	}
	res->AddEntity(ret);
	return ret;
}

void TemplateManager::AddCompTemp(TComponent * toadd)
{
	ctemps.push_back(toadd);
}

void TemplateManager::CreateEntTemp(std::string tname, std::vector<TComponent*> tcomps)
{
	TEntity* nte = new TEntity(tname);
	nte->temps = tcomps;
	temps.push_back(nte);
}




TemplateManager::TemplateManager(RebEntitySystem * sres)
{
	res = sres;
	temps.clear();
	ctemps.clear();
}


TemplateManager::~TemplateManager()
{
	for (unsigned int i = 0; i < temps.size(); i++)
	{
		delete temps[i];
	}
	temps.clear();


	for (unsigned int i = 0; i < ctemps.size(); i++)
	{
		delete ctemps[i];
	}
	ctemps.clear();
}



RebEntitySystem::RebEntitySystem()
{
	ents.clear();
	tm = new TemplateManager(this);
}

void RebEntitySystem::AddEntity(Entity * ent)
	{
		ents.push_back(ent);
	}

void RebEntitySystem::Update()
{
	for(unsigned int i = 0; i < ents.size(); i++)
	{
		ents[i]->UpdateAllComps();
	}
}
	
TemplateManager * RebEntitySystem::GetTemplateManager()
	{
		return tm;
	}

Entity * RebEntitySystem::GetEntity(std::string name)
	{
		for (unsigned int i = 0; i < ents.size(); i++)
		{
			if(ents[i]->GetID() == name)
			{
				return ents[i];
			}
		}
		return 0;
	}

	

void RebEntitySystem::Release()
{
	for (unsigned int i = 0; i <  ents.size(); i++)
	{
		delete ents[i];
	}
	ents.clear();
	delete tm;
}

RebEntitySystem::~RebEntitySystem()
{
}