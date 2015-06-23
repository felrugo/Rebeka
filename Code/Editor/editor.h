#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"
#include "../RebGraphic/RebGraphicSystem.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebTimer.h"
#include "..\RebSupport\RebString.h"
#include "..\RebSupport\RebVL.h"

class Editor : public QMainWindow, public IWindowManager
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	void Init();
	void EditorLoop();
	void Release();


	void InitManager() {}

	void ReleaseManager() {}

	void CreateWin(std::string name, int w, int h, int posx = 0, int posy = 0) {}

	void DestroyWindow(std::string name) {}

	void* GetWindow(std::string name) { return 0; }

	void EnableRender(std::string name) {}

	void SwapWindow(void * window) {}

	void DisableRender(std::string name) {}

	void TrapMouse(bool trap) {}



	~Editor();

private:
	Ui::EditorClass ui;

	RebGraphicSystem rgs;
	RebAudioSystem ras;
	IRenderDevice * rd;
	RebEntitySystem * res;
	RebFileSystem * rfs;
	void * window;
	bool gr;


	RebGDC * mGDC;
};

#endif // EDITOR_H
