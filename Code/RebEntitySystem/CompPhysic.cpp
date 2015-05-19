#include "CompPhysic.h"


CompPhyModel::CompPhyModel(btDynamicsWorld * SDW, IRenderDevice * SIRD, std::string smf)
{
	DW = SDW;
	IRD = SIRD;
	mf = smf;
}

void CompPhyModel::LoadPhysic()
{
	/*RebVertexCache * RVC = IRD->GetVertexCacheManager()->GetVCByFile(mf);
	if(RVC == 0)
	{
		IRD->GetVertexCacheManager()->CreateCacheFromFile(mf, mf);
		RVC = IRD->GetVertexCacheManager()->GetVCByFile(mf);
		if(RVC == 0)
		{
			return;
		}
	}
	for (unsigned int i = 0; i < RVC->RVBs.size(); i++)
	{
	
			
			btConvexHullShape * modshape = new btConvexHullShape();

			for (unsigned int i2 = 0; i2 < RVC->RVBs[i].vertices.size(); i2++)
			{
				btVector3 vec(RVC->RVBs[i].vertices[i2].x, RVC->RVBs[i].vertices[i2].y, RVC->RVBs[i].vertices[i2].z);
				modshape->addPoint(vec);
			}
			btQuaternion rot(RVC->RVBs[i].trans.ori.x, RVC->RVBs[i].trans.ori.y, RVC->RVBs[i].trans.ori.z, 1);
			btVector3 tra;
			tra.setX(RVC->RVBs[i].trans.GetTranslation().x);
			tra.setY(RVC->RVBs[i].trans.GetTranslation().y);
			tra.setZ(RVC->RVBs[i].trans.GetTranslation().z);
			btDefaultMotionState*mState =
                new btDefaultMotionState(btTransform(rot, tra));

			btRigidBody::btRigidBodyConstructionInfo
				groundRigidBodyCI(0, mState, modshape, btVector3(0,0,0));
        btRigidBody* StaticRigidBody = new btRigidBody(groundRigidBodyCI);

		DW->addRigidBody(StaticRigidBody);
	
		}*/
	}
	
