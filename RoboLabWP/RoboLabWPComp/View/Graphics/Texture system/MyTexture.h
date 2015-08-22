#pragma once

#include "tga_utils.h"

#include <string>
#include "EGL/egl.h"

using namespace std;

class MyTexture
{
public:
	MyTexture(string path, string name);
	~MyTexture(void);
	GLuint loadtexture(const string &path);

	GLuint texture();
	string name();

private:
	GLuint _texture;
	string _name;
};

