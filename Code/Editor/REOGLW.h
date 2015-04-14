#ifndef REOGLW_H
#define REOGLW_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "..\RebRenderer\IRenderer.h"


class REOGLW : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
	IRenderDevice * ird;

public:
	explicit REOGLW(QWidget *parent = 0);
	~REOGLW() {}
	void SetRenderer(IRenderDevice * sird);
	void cleanup() {}

signals:

	public slots:

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	

};



#endif