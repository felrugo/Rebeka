#include "RebGame.h"



void CreateGameDLL(IGameDLL **IGDLL)
{
	*IGDLL = new RebGame;
}

void ReleaseGameDLL(IGameDLL **IGDLL)
{
	delete *IGDLL;
}


void RebGame::Init()
{
	
	rend.CreateDevice();

	ras.CreateAudioDevice();

	ras.GetAudioDevice()->Init();

	ras.GetAudioDevice()->GetMusicPlayer()->Init();

	ras.GetAudioDevice()->GetMusicPlayer()->SetSource("test.ogg");

	ras.GetAudioDevice()->GetMusicPlayer()->Play();

	

	

	winsys.CreateManager();
	winm = winsys.GetManager();
	winm->InitManager();
	winm->CreateWin("hello world", 800, 600, 100, 100);
	winm->EnableRender("hello world");
	window = winm->GetWindow("hello world");
	rend.GetDevice()->Init(winm, 800, 600);
	rd = rend.GetDevice();

	
	std::vector<TComponent*> tcomps;
	TComponent * viewcompt = new TCompVisViewport(rd);
	TComponent * inpconp = new TCompInpBasicControl(winsys.GetMEH());
	tcomps.push_back(viewcompt);
	tcomps.push_back(inpconp);
	res.GetTemplateManager()->CreateEntTemp("tviewport", tcomps);
	Entity * ent = res.GetTemplateManager()->CreateEntByTemp("testviwe", "tviewport");
	ent->SetPos(RebVector(0.0f, 0.0f, 0.0f));
	static_cast<CompVisViewport*>(ent->GetComponent("CompVisViewport"))->SetActiveViewport();

	RebMatrix m1, m2, m3;

	double err = cos(3.14159265 / 2);


	m1.Identity();
	m2.Identity();

	m1.Rota(0.0f, PI/2, 0.0f);

	m3 = m1 * m2;
	
	std::vector<RebVertexBuffer> buffs;
	RebVertexBuffer rvbtri;
	rvbtri.met = R_TRIANGLES;

	rvbtri.mm = MM_MODELVIEW;

	rvbtri.name = "triangle";
	rvbtri.Renderable = true;
	RebVector points(-1.0f, 0.0f, 0.0f);
	rvbtri.vertices.push_back(points);
	points.Set(1.0f, 0.0f, 0.0f);
	rvbtri.vertices.push_back(points);
	points.Set(0.0f, 1.0f, 0.0f);
	rvbtri.vertices.push_back(points);
	buffs.push_back(rvbtri);
	rd->GetVertexCacheManager()->CreateCache("trianglech", buffs);



	bool pressed = false;
	winm->TrapMouse(true);
}

void RebGame::GameLoop()
{
while(1)
	{
		RebEvent Event;
		rd->Clear(1, 1);
		rd->ResetMatrix();
	winsys.GetMEH()->TranslateEvent(&Event);
	res.Update();
		if(Event.Type == WE_QUIT)
		{
			break;
		}
		rd->Color(1.0f, 0.0f, 0.0f);
		rd->GetVertexCacheManager()->Render();
		rd->Swap(window);
   }
}

void RebGame::Release()
{
	winm->TrapMouse(false);
	res.Release();
	ras.GetAudioDevice()->GetMusicPlayer()->Stop();
	rend.GetDevice()->Release();
	winm->DisableRender("hello world");
	winm->DestroyWindow("hello world");
	winm->ReleaseManager();
	winsys.DeleteManager();
	rend.ReleaseDevice();
	ras.ReleaseAudioDevice();
}