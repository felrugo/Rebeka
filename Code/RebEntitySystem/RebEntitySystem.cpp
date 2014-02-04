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



void TemplateManager::CreateEntTemp(std::string tname, std::vector<TComponent*> tcomps)
{
	TEntity* nte = new TEntity(tname);
	nte->temps = tcomps;
	temps.push_back(nte);
}

void TemplateManager::LoadTComps()
{
	if(res->GameData->rd != 0)
	ctemps["CompVisViewport"] = new TCompVisViewport(res->GameData->rd);
	ctemps["CompVisModel"] = new TCompVisModel(res->GameData->rd);
	if(res->GameData->meh != 0)
	ctemps["CompInpBasicControl"] = new TCompInpBasicControl(res->GameData->meh);
}


TemplateManager::TemplateManager(RebEntitySystem * sres)
{
	Loaded = false;
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


	for(std::map<std::string, TComponent *>::iterator it = ctemps.begin(); it != ctemps.end(); ++it) {
		delete ctemps[(it->first)];
}
	ctemps.clear();
}



RebEntitySystem::RebEntitySystem(RebGDC * sgd)
{
	ents.clear();
	GameData = sgd;
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