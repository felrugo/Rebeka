#include "REOGLW.h"


void REOGLW::initializeGL()
{
	initializeOpenGLFunctions();
	glClear(GL_COLOR_BUFFER_BIT);
}
void REOGLW::paintGL()
{
	makeCurrent();
	glViewport(0, 0, 500, 500);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, 500, 0, 500, 0, -100);
	glOrtho(-1,1,1,1,0,-1);

	//glMatrixMode(GL_MODELVIEW);

	//glLoadIdentity();
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0, 1, 0, 1);
	//glColor3f(1, 0, 0);

	//glMatrixMode(GL_PROJECTION);

	//const int x = 100;
	//int y = 100;

	//const int dx = 26;
	//const int dy = 16;

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();

	
}
void REOGLW::resizeGL(int width, int height)
{
	if (ird)
		ird->SetVP(width, height);
}

void REOGLW::SetRenderer(IRenderDevice * sird)
{
	ird = sird;
}

REOGLW::REOGLW(QWidget *parent) : QOpenGLWidget(parent)
{
	ird = 0;
	
}