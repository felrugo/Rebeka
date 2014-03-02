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
	winsys.CreateManager();
	winm = winsys.GetManager();
	winm->InitManager();
	winm->CreateWin("hello world", 800, 600, 100, 100);
	winm->EnableRender("hello world");
	window = winm->GetWindow("hello world");

	rend.CreateDevice();
	rend.GetDevice()->Init(winm, 800, 600);
	rd = rend.GetDevice();

	ras.CreateAudioDevice();
	ras.GetAudioDevice()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->Init();
	ras.GetAudioDevice()->GetMusicPlayer()->SetSource("test.ogg");
	ras.GetAudioDevice()->GetMusicPlayer()->Play();


	//test

	RebVector look(0, 0, -1);
	RebVector up(0, 1, 0);
	RebMatrix rm;
	rm.Identity();
	rm.RotyByDeg(90, -90, 0);
	look = look * rm;
	up = up * rm;
	rm.RotyByDeg(-30, 0, 0);
	look = look * rm;
	RebVector ori;
	ori.x = acos(look.y) * 180/PI;
	ori.y = asin(-look.x) * 180/PI;
	

	rfs = new RebFileSystem;
	rfs->GetAllFiles("..\\..");
	rfs->Categorize();

	mGDC = new RebGDC;
	mGDC->rd = rd;
	mGDC->window = window;
	mGDC->winm = winm;
	mGDC->meh = winsys.GetMEH();
	mGDC->rfs = rfs;

	UINT shaderp, sh;

	rd->GetShaderSystem()->CreateProgram("inversec", &shaderp);
	rd->GetShaderSystem()->AddShader(rfs->Search("inversec.rfs", "Shaders").rpath, shaderp, &sh);
	rd->GetShaderSystem()->ActivateProgram(sh);


	res = new RebEntitySystem(mGDC);
	std::vector<TComponent*> tcomps;
	TComponent * viewcompt = new TCompVisViewport(rd);
	TComponent * inpconp = new TCompInpBasicControl(winsys.GetMEH());
	tcomps.push_back(viewcompt);
	tcomps.push_back(inpconp);
	res->GetTemplateManager()->CreateEntTemp("tviewport", tcomps);
	Entity * ent = res->GetTemplateManager()->CreateEntByTemp("testviwe", "tviewport");

	ent->SetPos(RebVector(0.0f, 0.0f, 0.0f));
	static_cast<CompVisViewport*>(ent->GetComponent("CompVisViewport"))->SetActiveViewport();



	rd->GetVertexCacheManager()->CreateCacheFromFile("testbox", rfs->Search("phybox.obj").rpath);

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
	res->Update();
		if(Event.Type == WE_QUIT)
		{
			break;
		}
		rd->GetVertexCacheManager()->Render();
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
	winm->DisableRender("hello world");
	winm->DestroyWindow("hello world");
	winm->ReleaseManager();
	winsys.DeleteManager();
	rend.ReleaseDevice();
	delete res;
	delete rfs;
	ras.ReleaseAudioDevice();
}