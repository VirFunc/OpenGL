#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include "glad.h"

class Shader
{
private:
	unsigned int proID = 0;
	void checkCompileErrors(unsigned int shader, std::string type);
public:
	Shader() {};
	~Shader();
	Shader(const Shader&s);
    bool build_from_file(const std::string vertexPath,const std::string fragmentPath);
	bool build_from_memory(const char*,const char*);
	void use();
	unsigned int ID() const { return proID; };
	void set_bool(const std::string &name, bool value) const;
	void set_int(const std::string &name, int value) const;
	void set_float(const std::string &name, float value) const;
	void set_mat4f(const std::string &name, float* value) const;
};