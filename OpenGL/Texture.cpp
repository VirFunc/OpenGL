#include"Texture.h"
bool Texture::load_from_file(const std::string& path, bool mip, unsigned int unit)
{
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		return false;
	}
	tex_unit = unit;
	is_mipmap = mip;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + tex_unit);
	glBindTexture(GL_TEXTURE_2D, texture);
	//texture_setting--------------
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	if (is_mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Texture::create_mipmap()
{
	if (!is_mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		is_mipmap = true;
	}
}

void Texture::destroy()
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
	}
}

void Texture::use()
{
	glActiveTexture(GL_TEXTURE0 + tex_unit);
	glBindTexture(GL_TEXTURE_2D, texture);
}