#include "editor.h"

Editor::Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Editor::~Editor()
{
	
}

void Editor::onBut1Press()
{
	ui.label->setText("asdasdas");
}