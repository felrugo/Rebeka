#include "rebedit.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RebEdit w;
	w.show();
	return a.exec();
}
