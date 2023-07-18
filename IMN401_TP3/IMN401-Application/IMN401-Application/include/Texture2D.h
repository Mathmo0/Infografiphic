#pragma once


#include <string>
#include "Scene.h"

class Texture2D
{
public:

	Texture2D(const std::string& filename);

	~Texture2D();


	void loadToGPU();
	void makeResident();


	GLuint getId() {
		return id;
	};
	GLuint64 getHandle()
	{
		return handle;
	}

protected:
	GLuint id;
	GLuint64 handle;
	string name;
	int width, height;
	

	unsigned char* image;



};