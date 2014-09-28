#include "RebGame.h"



void CreateGameDLL(IGameDLL **IGDLL)
{
	*IGDLL = new RebGame;
}

void ReleaseGameDLL(IGameDLL **IGDLL)
{
	delete *IGDLL;
}

int dost()
{
	int a = 5;
	return a;
}

void RebGame::Init()
{

	mGDC = new RebGDC;
	
	

	rfs = new RebFileSystem;
	rfs->GetAllFiles("..\\..");
	rfs->Categorize();

	mGDC->rfs = rfs;
	mGDC->grp = &gr;


	winsys.CreateManager();
	winm = winsys.GetManager();
	winm->InitManager();
	winm->CreateWin("Launcher", 1280, 720, 100, 100);
	winm->EnableRender("Launcher");
	window = winm->GetWindow("Launcher");

	mGDC->window = window;
	mGDC->winm = winm;
	mGDC->meh = winsys.GetMEH();


	rend.CreateDevice();
	rend.GetDevice()->Init(mGDC);
	rd = rend.GetDevice();
	rd->SetVP(1280, 720);

	ras.CreateAudioDevice();
	ras.GetAudioDevice()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->SetSource("test.ogg");
	ras.GetAudioDevice()->GetMusicPlayer()->Play();
	

	

	RebTimer rtimer;

	res = new RebEntitySystem(mGDC);
	std::vector<TComponent*> tcomps;
	TComponent * viewcompt = new TCompVisViewport(rd);
	TComponent * inpconp = new TCompInpBasicControl(winsys.GetMEH());
	tcomps.push_back(viewcompt);
	tcomps.push_back(inpconp);
	res->GetTemplateManager()->CreateEntTemp("tviewport", tcomps);
	Entity * ent = res->GetTemplateManager()->CreateEntByTemp("testviwe", "tviewport");
	res->GetTemplateManager()->CreateEntByTemp("Ter1", "Terrain");
	ent->SetPos(RebVector(0.0f, 0.0f, 0.0f));
	static_cast<CompVisViewport*>(ent->GetComponent("CompVisViewport"))->SetActiveViewport();



	rd->GetVertexCacheManager()->CreateCacheFromFile("testbox1", rfs->Search("phybox.obj").rpath);
	rd->GetVertexCacheManager()->CreateCacheFromFile("testbox2", rfs->Search("phybox.obj").rpath);
	rd->GetVertexCacheManager()->CreateCacheFromFile("testbox3", rfs->Search("phybox.obj").rpath);
	//
	rd->GetVertexCacheManager()->GetVertexCache("testbox2")->transf.Scale(0.01f, 0.01f, 0.01f);
	rd->GetVertexCacheManager()->GetVertexCache("testbox2")->transf.Translate(0, 1, 0);
	rd->GetVertexCacheManager()->GetVertexCache("testbox3")->transf.Scale(0.05f, 0.05f, 0.05f);
	rd->GetVertexCacheManager()->GetVertexCache("testbox3")->transf.Translate(0, 1, 4);
	bool pressed = false;
	winm->TrapMouse(true);

	gr = true;
}

void RebGame::GameLoop()
{
while(gr)
	{
		RebEvent Event;
		winsys.GetMEH()->TranslateEvent(&Event);
		if(Event.Type == WE_QUIT)
		{
			gr = false;
		}
		res->Update();
		rd->Render();
		rd->Swap(window);
   }
}

void RebGame::Release()
{
	winm->TrapMouse(false);
	delete mGDC;
	res->Release();
	ras.GetAudioDevice()->GetMusicPlayer()->Stop();
	rend.GetDevice()->Release();
	winm->DisableRender("Launcher");
	winm->DestroyWindow("Launcher");
	winm->ReleaseManager();
	winsys.DeleteManager();
	rend.ReleaseDevice();
	delete res;
	delete rfs;
	ras.ReleaseAudioDevice();
}