#pragma once
#include "glad.h"
class Mesh
{
private:
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	unsigned int amount = 0;
	unsigned int number = 0;
	bool is_element = false;
public:
	Mesh() {};
	~Mesh();
	Mesh(const Mesh&) = delete;
	Mesh(float* p, unsigned int count, GLenum usage);
	bool tex_build(float* verTexCoord, unsigned int count, GLenum usage);
	bool build(float* p, unsigned int count, GLenum usage);
	bool set_element(unsigned int* p, unsigned int count, GLenum usage);
	void draw(GLenum pattern);
	void destoy();
};
//Tools
bool make_tex_cube(Mesh* m);
bool make_cube(float len, Mesh* m);