#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"
#include "../RebRenderer/IRenderer.h"
#include "..\RebAudio\RebAudioSystem.h"
#include "..\RebEntitySystem\RebEntitySystem.h"
#include "..\RebSupport\RebGDC.h"
#include "..\RebSupport\RebFileSystem.h"
#include "..\RebSupport\RebTimer.h"
#include "..\RebSupport\RebString.h"
#include "..\RebSupport\RebVL.h"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	void Init();
	void EditorLoop();
	void Release();
	~Editor();

private:
	Ui::EditorClass ui;

	Renderer rend;
	RebAudioSystem ras;
	IRenderDevice * rd;
	RebEntitySystem * res;
	RebFileSystem * rfs;
	void * window;
	bool gr;


	RebGDC * mGDC;
};

#endif // EDITOR_H
