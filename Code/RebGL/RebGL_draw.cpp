#include "RebGL.h"


void RebGL::StartDraw(Methold met)
{
	switch (met)
	{
	case R_TRIANGLES:
		glBegin(GL_TRIANGLES);
		break;
	case R_QUADS:
		glBegin(GL_QUADS);
		break;
	default:
		glBegin(GL_TRIANGLES);
		break;
	}
}

void RebGL::EndDraw()
{
	glEnd();
}

void RebGL::Vertex3(float x, float y, float z)
{
	glVertex3f(x, y, z);
}

void RebGL::Vertex3(RebVector RV)
{
	glVertex3f(RV.x, RV.y, RV.z);
}

void RebGL::TextCoord2(float s, float t)
{
	glTexCoord2f(s, t);
}

void RebGL::BindTexture(UINT id)
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void RebGL::Color(float r, float g, float b)
{
	glColor3f(r, g, b);
}


void RebGL::Normal(RebVector RV)
{
	glNormal3f(RV.x, RV.y, RV.z);
}

void RebGL::MaterialSetup(RebMaterial rm)
{
	float amb[] = {rm.amb.fR, rm.amb.fG, rm.amb.fB, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	float dif[] = {rm.dif.fR, rm.dif.fG, rm.dif.fB, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	float spe[] = {rm.spe.fR, rm.spe.fG, rm.spe.fB, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
}


void RebGL::Swap(void * window)
{
	iwm->SwapWindow(window);
}

void RebGL::ChangeMatrixMode(MatrixMode mm)
{
	switch (mm)
	{
	case MM_MODELVIEW:
		glMatrixMode(GL_MODELVIEW);
		break;
	case MM_PROJECTIONVIEW:
		glMatrixMode(GL_PROJECTION);
		break;
	default:
		glMatrixMode(GL_MODELVIEW);
		break;
	}
}

void RebGL::ResetMatrix()
{
	glLoadIdentity();
}

	void RebGL::PushMatrix()
	{
		glPushMatrix();
	}

	void RebGL::PopMatrix()
	{
		glPopMatrix();
	}

	void RebGL::Flush()
	{
		glFlush();
	}


	void RebGL::Translate(float x, float y, float z)
	{
		glTranslatef(x, y, z);
	}

	void RebGL::Rotate(float a, float x, float y, float z)
	{
		glRotatef(a, x, y ,z);
	}

	void RebGL::Scale(float x, float y, float z)
	{
		glScalef(x, y, z);
	}

	void RebGL::TransformMatrix(RebMatrix trans)
	{
		/*RebVector v(0.0f, 0.0f, 0.0f);

		glRotatef(trans.ori.x, 1.0f, 0.0f, 0.0f);
		glRotatef(trans.ori.y, 0.0f, 1.0f, 0.0f);
		glRotatef(trans.ori.z, 0.0f, 0.0f, 1.0f);
		glTranslatef(trans.GetTranslation().x, trans.GetTranslation().y, trans.GetTranslation().z);*/

		float m[] = {trans._11, trans._12, trans._13, trans._14, 
					trans._21, trans._22, trans._23, trans._24, 
					trans._31, trans._32, trans._33, trans._34, 
					trans._41, trans._42, trans._43, trans._44};

		glLoadMatrixf(m);

	}