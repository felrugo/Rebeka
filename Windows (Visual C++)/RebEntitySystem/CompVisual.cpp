#include "CompVisual.h"


CompVisModel::CompVisModel(IRenderDevice * sird, std::string smf)
	{
		IRD = sird;
		mf = smf;
	}


void CompVisModel::LoadModel(std::string filename)
	{
		IRD->GetVertexChacheManager()->CreateChacheFromFile(GetOwner()->GetID(), filename);
		rvc = IRD->GetVertexChacheManager()->GetVertexChache(GetOwner()->GetID());
	}


TCompVisModel::TCompVisModel(IRenderDevice * sird, std::string mf)
	{
		IRD = sird;
		ModelFile = mf;
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