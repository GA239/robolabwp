#include "pch.h"
#include "MyTexture.h"


MyTexture::MyTexture(string path, string name)
{
	_texture = loadtexture(path);
	_name = name;
}


MyTexture::~MyTexture(void)
{
	glDeleteTextures(1, &_texture);
}


GLuint MyTexture::loadtexture(const string &path)
{
	TGAImage img;
	if (!LoadTGAImageFromFile(path, &img))
	{
		return 0;
	}

	return LoadTextureFromTGAImage(img);
}

GLuint MyTexture::texture()
{
	return _texture;
}
string MyTexture::name()
{
	return _name;
}