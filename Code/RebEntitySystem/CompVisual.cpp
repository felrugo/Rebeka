#include "CompVisual.h"


CompVisModel::CompVisModel(IRenderDevice * sird)
	{
		IRD = sird;
	}


void CompVisModel::LoadModel(std::string filename)
	{
		IRD->GetVertexCacheManager()->CreateCacheFromFile(GetOwner()->GetID(), filename);
		rvc = IRD->GetVertexCacheManager()->GetVertexCache(GetOwner()->GetID());
	}

void CompVisModel::update()
{
	if(Params["isModelChanged"] == 1)
	{
		IRD->GetVertexCacheManager()->DeleteCache(rvc);
		LoadModel(Params["Model"]);
		Params["isModelChanged"] = 0;
	}
}


TCompVisModel::TCompVisModel(IRenderDevice * sird)
	{
		IRD = sird;
	}

CompVisViewport::CompVisViewport(IRenderDevice * SIRD)
{
	IRD = SIRD;
}

void CompVisViewport::update()
{
	if((CompVisViewport*)*IRD->GetViewportID() == this)
	{
		RebMatrix mt, mr;
		mt.Identity();
		mr.Identity();
		mr.RotyByDeg(-GetOwner()->GetOri().x, -GetOwner()->GetOri().y, -GetOwner()->GetOri().z);
		mt.Translate(-GetOwner()->GetPos().x, -GetOwner()->GetPos().y, -GetOwner()->GetPos().z);
		IRD->SetViewportMat(mt * mr);
	}

}

void CompVisViewport::SetActiveViewport()
{
	*IRD->GetViewportID() = this;
}

TCompVisViewport::TCompVisViewport(IRenderDevice * sird)
{
	IRD = sird;
}