#include "RebEnv.h"



RebGLTerrain::RebGLTerrain()
{
	stepx = 0;
	stepy = 0;
	stepsize = 1;
	trans.Identity();
	Hps.clear();
	loaded = false;
	vbo[0] = vbo[1] = 0;
}


void RebGLTerrain::LoadFromFile(std::string rtf)
{

}


void RebGLTerrain::LoadFlat(int x, int y)
{
	stepx = x;
	stepy = y;
	Hps.clear();
	for (size_t iy = 0; iy < y; iy++)
	{
		for (size_t ix = 0; ix < x; ix++)
		{
			Hps.push_back(0.0f);
		}
	}
}

RebVector CalcNorm(RebVector * nvs)
{
	RebVector e1, e2, norm;
	e1 = nvs[1] - nvs[0];
	e2 = nvs[2] - nvs[0];
	norm.Cross(e1, e2);
	norm.Normalize();
	return norm;
}

void RebGLTerrain::LoadIntoGL()
{
	if (loaded == false && stepy >= 2)
	{
		glGenBuffers(2, vbo);

		float * buffdata;
		unsigned long size = Hps.size() + stepx * (stepy - 2);
		buffdata = new float[size * 3];
		float * normaldata = new float[size * 3];
		RebVector nvs[3];
		unsigned int faster = 0;
		unsigned int fn = 0;
		unsigned int inrow = 0;
		for (size_t iy = 0; iy < stepy - 1; iy++)
		{
			for (size_t ix = 0; ix < stepx; ix++)
			{
				for (size_t i = 0; i < 2; i++)
				{
					RebVector v(float(ix) * stepsize, Hps[(iy + i)*stepx + ix], (iy + i)*stepsize);
					inrow++;
					nvs[inrow % 3] = v;
					buffdata[faster] = v.x;
					buffdata[faster + 1] = v.y;
					buffdata[faster + 2] = v.z;
					
					if (inrow == 3)
					{
						for (size_t i = 0; i < 3; i++)
						{
							normaldata[fn] = CalcNorm(nvs).x;
							normaldata[fn + 1] = CalcNorm(nvs).y;
							normaldata[fn + 2] = CalcNorm(nvs).z;
							fn += 3;
						}
					}
					if (inrow > 3)
					{
						normaldata[fn] = CalcNorm(nvs).x;
						normaldata[fn + 1] = CalcNorm(nvs).y;
						normaldata[fn + 2] = CalcNorm(nvs).z;
						fn += 3;
					}
					faster += 3;
				}
		
			}
		}



		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

		glBufferData(GL_ARRAY_BUFFER, 3 * size * sizeof(float), buffdata, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

		glBufferData(GL_ARRAY_BUFFER, 3 * size * sizeof(float), normaldata, GL_STATIC_DRAW);

		

			delete[] buffdata;
			delete[] normaldata;
			loaded = true;
		}
		

	}


void RebGLTerrain::Draw()
{
	if (!loaded)
		LoadIntoGL();


	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);         // for vertex coordinates

	// do same as vertex array except pointer
	glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
	glVertexPointer(3, GL_FLOAT, 0, 0);               // last param is offset, not ptr

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);         // for vertex coordinates

	// do same as vertex array except pointer
	glEnableClientState(GL_NORMAL_ARRAY);             // activate vertex coords array
	glNormalPointer(GL_FLOAT, 0, 0);

	
	unsigned long size = Hps.size() + stepx * (stepy - 2);
	// draw 6 quads using offset of index array
	glDrawArrays(GL_TRIANGLE_STRIP, 0, size);

	glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array
	glDisableClientState(GL_NORMAL_ARRAY);            // deactivate vertex array
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);            // deactivate vertex array

	// bind with 0, so, switch back to normal pointer operation
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}











RebEnv::RebEnv()
{
	Terrains.clear();
}

RebTerrain * RebEnv::CreateTerrain()
{
	RebGLTerrain * ret = new RebGLTerrain();
	Terrains.push_back(ret);
	ret->LoadFlat(3, 3);
	ret->LoadIntoGL();
	return ret;
}


RebTerrain * RebEnv::CreateTerrain(std::string hmf)
{
	RebTerrain * ret = new RebGLTerrain();

	/*RebIH ih;
	ih.LoadFile(hmf);
	unsigned int w, h;
	w = ih.GetWidth();
	h = ih.GetHeight();

	ret->stepx = w;
	ret->stepy = h;

	for (unsigned int i = 0; i < h; i++)
	{
		for (unsigned int i2 = 0; i2 < w; i2++)
		{
			float push = ih.GetPixelColor(w, h).x;
			ret->Hps.push_back(push);
		}
	}


	Terrains.push_back(ret);*/
	return ret;
}

std::vector<RebTerrain*> * RebEnv::GetTerrains()
{
	return &Terrains;
}

void RebEnv::DeleteTerrain(RebTerrain * del)
{
	for(unsigned int i = 0; i < Terrains.size(); i++)
	{
		if(Terrains[i] == del)
		{
			delete Terrains[i];
			Terrains.erase(Terrains.begin() + i);
		}
	}
}