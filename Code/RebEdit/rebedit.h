#ifndef REBEDIT_H
#define REBEDIT_H

#include <QtWidgets/QMainWindow>
#include "ui_rebedit.h"

class RebEdit : public QMainWindow
{
	Q_OBJECT

public:
	RebEdit(QWidget *parent = 0);
	~RebEdit();

private:
	Ui::RebEditClass ui;
};

#endif // REBEDIT_H
