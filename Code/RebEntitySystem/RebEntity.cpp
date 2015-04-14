#include "RebEntity.h"


TEntity::TEntity(std::string sname)
{
	temps.clear();
	name = sname;
}

	TEntity::~TEntity()
	{
			Clear();
	}

	void TEntity::SetName(std::string ID)
	{
		name = ID;
	}

	std::string TEntity::GetName()
	{
		return name;
	}

	TComponent * TEntity::GetTemplate(std::string ID)
	{
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			if(temps[i]->GetID() == ID)
			{
				return temps[i];
			}
		}
		return 0;
	}

	void TEntity::AddTemplate(TComponent * atemp)
	{
		temps.push_back(atemp);
	}

	void TEntity::Clear()
	{
		for (unsigned int i = 0; i < temps.size(); i++)
		{
			delete temps[i];
		}
		temps.clear();
	}
	
	std::vector<TComponent*> * TEntity::GetTComps()
	{
		return &temps;
	}



	Entity::Entity(std::string ID)
	{
		name = ID;
		comps.clear();
	}

	void Entity::SetID(std::string ID)
	{
		name = ID;
	}

	std::string Entity::GetID()
	{
		return name;
	}

	Component * Entity::GetComponent(std::string ID)
	{
		for (unsigned int i = 0; i < comps.size(); i++)
		{
			if(comps[i]->GetID() == ID)
			{
				return comps[i];
			}
		}
		return 0;
	}

	Component * Entity::SetComponent(Component * scomp)
	{
		if(GetComponent(scomp->GetID()) != 0)
		{
			return GetComponent(scomp->GetID());
		}
		else
		{
			scomp->SetOwner(this);
			comps.push_back(scomp);
			return 0;
		}
	}

	void Entity::UpdateAllComps()
	{
		for(unsigned int i = 0; i < comps.size(); i++)
		{
			comps[i]->update();
		}
	}

	void Entity::ClearComps()
	{
		for (unsigned int i = 0; i < comps.size(); i++)
		{
			delete comps[i];
		}
		comps.clear();
	}

	RebVector Entity::GetPos()
	{
		return pos;
	}

	RebVector Entity::GetOri()
	{
		return ori;
	}

	void Entity::SetPos(RebVector spos)
	{
		pos = spos;
	}

	void Entity::SetOri(RebVector sori)
	{
		ori.x = std::fmod(sori.x, 360);
		ori.y = std::fmod(sori.y, 360);
		ori.z = std::fmod(sori.z, 360);
	}

	Entity::~Entity()
	{
		ClearComps();
	}