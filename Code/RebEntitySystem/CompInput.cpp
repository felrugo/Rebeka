#include "CompInput.h"



CompInpBasicControl::CompInpBasicControl(IMEH * seh)
{
	eh = seh;
	x = y = 0.0f;
	keypressedmap.clear();
	eh->RegisterKeyEventListener(this);
	eh->RegisterMouseEventListener(this);
	keypressedmap.insert(std::pair<int, bool>(REBK_w, false));
	keypressedmap.insert(std::pair<int, bool>(REBK_a, false));
	keypressedmap.insert(std::pair<int, bool>(REBK_s, false));
	keypressedmap.insert(std::pair<int, bool>(REBK_d, false));
	keypressedmap.insert(std::pair<int, bool>(REBK_LSHIFT, false));
	keypressedmap.insert(std::pair<int, bool>(REBK_ESCAPE, false));
}

CompInpBasicControl::~CompInpBasicControl()
{
	eh->UnRegisterKeyEventListener(this);
	keypressedmap.clear();
}

void CompInpBasicControl::onKeyEvent(RebEvent keyevent)
{
	for (std::map<int, bool>::iterator it = keypressedmap.begin(); it != keypressedmap.end(); it++)
	{
		if (keyevent.key.keysym.sym == it->first)
		{
			it->second = (keyevent.Type == WE_KEYDOWNEVENT);
		}
	}
}


float clamp(float what, float with)
{
	return std::fmin(std::fmax(what, -with), with);
}

void CompInpBasicControl::onMMotionEvent(RebEvent me)
{
 RebVector mv(-(me.mousemot.yrel) / 50.0f, -(me.mousemot.xrel) / 50.0f, 0.0f);
 RebVector newori(clamp((GetOwner()->GetOri() + mv).x, 90), (GetOwner()->GetOri() + mv).y, (GetOwner()->GetOri() + mv).z);
	GetOwner()->SetOri(newori);
}

void CompInpBasicControl::update()
{
	RebMatrix moovmat;
	moovmat.Identity();
	moovmat.RotyByDeg(GetOwner()->GetOri().x, GetOwner()->GetOri().y, GetOwner()->GetOri().z);

	float mult = 1;
	if (keypressedmap[REBK_LSHIFT])
		mult = 10;

	if(keypressedmap[REBK_w])
	{
		RebVector v(0.0f, 0.0f,	-0.001f);
		v = v * moovmat * mult;
		GetOwner()->SetPos(GetOwner()->GetPos() + v);
	}
	if(keypressedmap[REBK_a])
	{
		RebVector v(-0.001f, 0.0f,	0.0f);
		v = v * moovmat * mult;
		GetOwner()->SetPos(GetOwner()->GetPos() + v);
	}
	if(keypressedmap[REBK_s])
	{
		RebVector v(0.0f, 0.0f,	0.001f);
		v = v * moovmat * mult;
		GetOwner()->SetPos(GetOwner()->GetPos() + v);
	}
	if(keypressedmap[REBK_d])
	{
		RebVector v(0.001f, 0.0f, 0.0f);
		v = v * moovmat * mult;
		GetOwner()->SetPos(GetOwner()->GetPos() + v);
	}
	if(keypressedmap[REBK_ESCAPE])
	{
		RebEvent re;
		re.Type = WE_QUIT;
		re.quit.Type = WE_QUIT;
		eh->AddEvent(re);
	}
}

TCompInpBasicControl::TCompInpBasicControl(IMEH * seh)
{
	eh = seh;
}

Component * TCompInpBasicControl::MakeComponent()
{
	Component * ret = new CompInpBasicControl(eh);
	return ret;
}