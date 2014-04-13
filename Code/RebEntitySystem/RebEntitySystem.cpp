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


TComponent * TemplateManager::BuiltinComps(std::string cn, RebGDC * GameData)
{
	TComponent * ret = 0;
	if(cn == "CompVisModel")
		ret = new TCompVisModel(GameData->rd);
	if(cn == "CompVisTerrain")
		ret = new TCompVisTerrain(GameData->rd);
		return ret;
}

TComponent * TemplateManager::TCFactory(std::string compname)
{
	TComponent * ret = 0;
	for (unsigned int i = 0; i < CTFF.size(); i++)
	{
		ret = CTFF[i](compname, res->GameData);
	}
	return ret;
}


TemplateManager::TemplateManager(RebEntitySystem * sres)
{
	Loaded = false;
	res = sres;
	temps.clear();
	CTFF.clear();
	CTFF.push_back(BuiltinComps);
	LoadDef();
	LoadEntTemps();
}



void TemplateManager::LoadDef()
{
	TEntity * ter = new TEntity("Terrain");
	ter->AddTemplate(TCFactory("CompVisTerrain"));
	temps.push_back(ter);
}

void TemplateManager::LoadEntTemps()
{
	tinyxml2::XMLDocument xd;
	for (unsigned int i = 0; i < res->GameData->rfs->GetEntities()->size(); i++)
	{
		xd.LoadFile(res->GameData->rfs->GetEntities()->at(i).rpath.c_str());
		std::string name = xd.FirstChild()->ToElement()->Attribute("name");
		TEntity * nt = new TEntity(name);
		tinyxml2::XMLNode * xn = xd.FirstChild()->FirstChild();
		while(xn->ToElement()->Name() == std::string("Component"))
		{
			tinyxml2::XMLElement * xe = xn->ToElement()->FirstChildElement();
			std::string compn = xn->ToElement()->Attribute("name");
			TComponent * tc = TCFactory(compn);
			if(tc == 0) break;
		while(xe->Name() == std::string("Param"))
		{
			tc->TParams[xe->Attribute("name")] = xe->Attribute("value");
			xe = xe->NextSiblingElement();
			if(xe == 0)
				break;
		}
		nt->AddTemplate(tc);
		xn = xn->NextSibling();
		if(xn == 0)
			break;
		}
		temps.push_back(nt);
	}
}


TemplateManager::~TemplateManager()
{
	for (unsigned int i = 0; i < temps.size(); i++)
	{
		delete temps[i];
	}
	temps.clear();

	CTFF.clear();
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