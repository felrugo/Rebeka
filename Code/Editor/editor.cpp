#include "editor.h"

Editor::Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void Editor::Init()
{
	mGDC = new RebGDC;



	rfs = new RebFileSystem;
	rfs->GetAllFiles("..\\..");
	rfs->Categorize();

	mGDC->rfs = rfs;
	mGDC->grp = &gr;


	/*winsys.CreateManager();
	winm = winsys.GetManager();
	winm->InitManager();
	winm->CreateWin("Launcher", 1280, 720, 100, 100);
	winm->EnableRender("Launcher");
	window = winm->GetWindow("Launcher");*/

	mGDC->window = 0;
	mGDC->winm = this;
	//mGDC->meh = winsys.GetMEH();


	rend.CreateDevice();
	rend.GetDevice()->Init(mGDC);
	rd = rend.GetDevice();
	ui.MainPerspective->makeCurrent();
	ui.MainPerspective->SetRenderer(rd);
	rd->SetVP(1280, 720);

	ras.CreateAudioDevice();
	//ras.GetAudioDevice()->Init();
	//ras.GetAudioDevice()->GetMusicPlayer()->Init();
	//ras.GetAudioDevice()->GetMusicPlayer()->SetSource(rfs->Search("daft.mp3", "Music").rpath);
	//ras.GetAudioDevice()->GetMusicPlayer()->Play();

	ras.GetAudioDevice()->Init();
	ras.GetAudioDevice()->GetSoundSystem()->Test();



	//RebTimer rtimer;

	//res = new RebEntitySystem(mGDC);
	//std::vector<TComponent*> tcomps;
	//TComponent * viewcompt = new TCompVisViewport(rd);
	//TComponent * inpconp = new TCompInpBasicControl(winsys.GetMEH());
	//tcomps.push_back(viewcompt);
	//tcomps.push_back(inpconp);
	//res->GetTemplateManager()->CreateEntTemp("tviewport", tcomps);
	//Entity * ent = res->GetTemplateManager()->CreateEntByTemp("testviwe", "tviewport");
	//res->GetTemplateManager()->CreateEntByTemp("Ter1", "Terrain");
	//ent->SetPos(RebVector(0.0f, 0.0f, 0.0f));
	//static_cast<CompVisViewport*>(ent->GetComponent("CompVisViewport"))->SetActiveViewport();



	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox1", rfs->Search("phybox.obj").rpath);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox2", rfs->Search("phybox.obj").rpath);
	//rd->GetVertexCacheManager()->CreateCacheFromFile("testbox3", rfs->Search("phybox.obj").rpath);
	////
	//rd->GetVertexCacheManager()->GetVertexCache("testbox2")->transf.Scale(0.01f, 0.01f, 0.01f);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox2")->transf.Translate(0, 1, 0);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox3")->transf.Scale(0.05f, 0.05f, 0.05f);
	//rd->GetVertexCacheManager()->GetVertexCache("testbox3")->transf.Translate(0, 1, 4);
	bool pressed = false;
	//winm->TrapMouse(true);

	//rd->Render();

	//glClearColor(1, 0, 0, 1);

	update();
	//gr = true;
}




Editor::~Editor()
{

}
