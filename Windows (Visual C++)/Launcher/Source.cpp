#include "../RebRenderer/IRenderer.h"
#include "..\RebWindowSystem\RebWindowSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"


bool game;

int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)             
{

	Renderer rend;
	rend.CreateDevice();

	RebAudioSystem ras;

	ras.CreateAudioDevice();

	ras.GetAudioDevice()->Init();

	ras.GetAudioDevice()->GetMusicPlayer()->Init();

	ras.GetAudioDevice()->GetMusicPlayer()->SetSource("test.ogg");

	ras.GetAudioDevice()->GetMusicPlayer()->Play();

	

	

	RebWindowSystem winsys;
	winsys.CreateManager();
	IWindowManager * winm = winsys.GetManager();
	winm->InitManager();
	winm->CreateWin("hello world", 800, 600, 100, 100);
	winm->EnableRender("hello world");
	void* window = winm->GetWindow("hello world");
	rend.GetDevice()->Init(winm, 800, 600);
	IRenderDevice * rd = rend.GetDevice();
	UINT id = 0;
	rd->GetSkinManager()->AddTexture("rebeka.jpg", &id);
	
	UINT invc;

	rd->GetShaderSystem()->CreateProgram(&invc);
	rd->GetShaderSystem()->AddShader("inversec.rvs", invc, 0);
	rd->GetShaderSystem()->AddShader("inversec.rfs", invc, 0);

	RebEntitySystem res;
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
	rd->GetVertexChacheManager()->CreateChache("trianglech", buffs);



	bool pressed = false;
	winm->TrapMouse(true);
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
		rd->GetVertexChacheManager()->Render();
		rd->Swap(window);
   }
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
	return 0;
}