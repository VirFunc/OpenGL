#pragma once
#include <string>
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
private:
	int width=0;
	int height=0;
	int channels=0;
	unsigned int texture;
	unsigned int tex_unit;
	bool is_mipmap=false;
	//debug
public:
	Texture(){};
	~Texture(){destroy();};
	bool load_from_file(const std::string& path,bool mip,unsigned int unit);
	void create_mipmap();
	void destroy();
	void use();
};