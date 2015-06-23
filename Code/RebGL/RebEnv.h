#ifndef REBENV
#define REBENV

#include "RebGL.h"

class RebGLTerrain : public RebTerrain
{
	bool loaded;
	GLuint vbo[2];
public:
	RebGLTerrain();

	void LoadFromFile(std::string rtf);

	void LoadIntoGL();

	void LoadFlat(int x, int y);

	void Draw();

	~RebGLTerrain();
};

class RebEnv : public IGameEnv
{
	std::vector<RebTerrain*> Terrains;
public:
	RebEnv();
	RebTerrain * CreateTerrain();
	RebTerrain * CreateTerrain(std::string hmf);
	std::vector<RebTerrain*> * GetTerrains();
	void DeleteTerrain(RebTerrain * del);
};



#endif