#include "Reb3d.h"


RebGLTrans::RebGLTrans()
{
	pos = RebVector(0.0f, 0.0f, 0.0f);
	ori = RebVector(0.0f, 0.0f, 0.0f);
}

RebGLTrans::RebGLTrans(RebVector spos, RebVector sori)
{
	pos = spos;
	ori = sori;
}

inline void RebGLTrans::Identity(void)
{
	pos = RebVector(0.0f, 0.0f, 0.0f);
	ori = RebVector(0.0f, 0.0f, 0.0f);
}

RebGLTrans RebGLTrans::operator + (const RebGLTrans &m)const
{
	RebGLTrans ret;
	ret.pos = pos + m.pos;
	ret.ori = m.ori;
	return ret;
}

RebGLTrans RebGLTrans::operator * (const RebGLTrans &m)const
{
	RebMatrix moovmat;
	moovmat.Identity();
	moovmat.RotyByDeg(ori.x, ori.y, ori.z);
	RebVector v;
	v = m.pos * moovmat;
	RebGLTrans ret;
	ret.pos = pos + m.pos;
	ret.ori = m.ori;
	return ret;
}