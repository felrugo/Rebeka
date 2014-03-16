#include "RebGL.h"



void CreateRenderDevice(IRenderDevice **LPRenderDevice)
{
	if(*LPRenderDevice == 0)
	*LPRenderDevice =  new RebGL;
}

void ReleaseRenderDevice(IRenderDevice **LPRenderDevice)
{
	if(*LPRenderDevice != 0)
	delete *LPRenderDevice;
}



void * RebGL::tm()
{

	return 0;
}

void RebGL::Init(IWindowManager * siwm, int width, int height)
{
glShadeModel( GL_SMOOTH );
 
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
 
    /* Depth buffer setup */
    glClearDepth( 1.0f );
 
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
 
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
 
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	 glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
 
	GLfloat ratio;

 
    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    }
 
	w = width;

	h = height;
	ratio = ( GLfloat )width / ( GLfloat )height;
    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );
 
    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );
 
    /* Reset The View */
    glLoadIdentity( );

	//init SkinManager
	iwm = siwm;

	skinman = new RebGLSkinManager;
	skinmanruning = true;

	VCM = new RebVertexCacheManager(this);
	VCMRunning = true;

	ISS = new RebShaderSystem;
	ISS->Init(this);

	ILS = new RebGLLightSystem();
	MatViewport.Identity();
}



void RebGL::GetViewportSize(unsigned int * sw, unsigned int * sh)
{
	*sw = w;
	*sh = h;
}



void RebGL::Release()
{

	if(skinmanruning)
	{
	delete skinman;
	delete ILS;
	skinmanruning = false;
	}

	if(VCMRunning)
	{
	delete VCM;
	
	VCMRunning = false;
	}
}

void RebGL::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
glClear(GL_COLOR_BUFFER_BIT);
}

void RebGL::Clear(bool color, bool depth)
{
	if (color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	if (depth)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}
}

RebGL::~RebGL()
{
	Release();
	delete ISS;
}


ISkinManager * RebGL::GetSkinManager()
{
	return skinman;
}

IVertexCacheManager * RebGL::GetVertexCacheManager()
{
	return VCM;
}

RebMatrix RebGL::GetViewportMat()
{
	return MatViewport;
}

void RebGL::SetViewportMat(RebMatrix svm)
{
	MatViewport = svm;
}

void ** RebGL::GetViewportID()
{
	return &ViewportID;
}

IShaderSystem * RebGL::GetShaderSystem()
{
	return ISS;
}