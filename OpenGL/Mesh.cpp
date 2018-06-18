#include"Mesh.h"
Mesh::Mesh(float* p, unsigned int count, GLenum usage)
{
	build(p, count, usage);
}

bool Mesh::build(float* p, unsigned int count, GLenum usage)
{
	amount = count;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (!(VAO&&VBO))
	{
		return false;
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, amount * 3 * sizeof(GLfloat), p, usage);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}

void Mesh::draw(GLenum pattern)
{
	glBindVertexArray(VAO);
	if (is_element)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(pattern, number, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(pattern, 0, amount);
	}
}

void Mesh::destoy()
{
	if (VAO != 0 && VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}
	if (EBO)
	{
		glDeleteBuffers(1, &EBO);
	}
}

Mesh::~Mesh()
{
	destoy();
}

bool Mesh::tex_build(float* verTexCoord, unsigned int count, GLenum usage)
{
	amount = count;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (!(VAO&&VBO))
	{
		return false;
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, amount * 5 * sizeof(GLfloat), verTexCoord, usage);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}

bool Mesh::set_element(unsigned int* ptr, unsigned int count, GLenum usage)
{
	glBindVertexArray(VAO);
	number = count;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, number * sizeof(unsigned int), ptr, usage);
	glBindVertexArray(0);
	is_element = true;
	return true;
}

bool make_cube(float len, Mesh* m)
{
	if (!m)
		return false;

	float pos[24];
	pos[0] = pos[3] = pos[12] = pos[15] = 0.5f*len;
	pos[6] = pos[9] = pos[18] = pos[21] = -0.5f*len;

	pos[1] = pos[4] = pos[7] = pos[10] = -0.5f*len;
	pos[13] = pos[16] = pos[19] = pos[22] = 0.5f*len;

	pos[2] = pos[11] = pos[14] = pos[23] = 0.5f*len;
	pos[5] = pos[8] = pos[17] = pos[20] = -0.5f*len;

	unsigned int ele[36] = {
		0,1,4,4,1,5, 1,2,5,5,2,6,
		2,3,6,6,3,7, 3,0,7,7,0,4,
		4,5,7,7,5,6, 0,3,1,1,3,2
	};

	m->build(pos, 24, GL_STATIC_DRAW);
	m->set_element(ele, 36, GL_STATIC_DRAW);
	return true;
}

bool make_tex_cube(Mesh* m)
{
	if (!m)
		return false;

	float pos[] = {
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	m->tex_build(pos, 36, GL_STATIC_DRAW);
	return true;
}
