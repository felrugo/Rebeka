#ifndef EDITOR_H
#define EDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	~Editor();

	private slots:
		void onBut1Press();

private:
	Ui::EditorClass ui;
};

#endif // EDITOR_H
