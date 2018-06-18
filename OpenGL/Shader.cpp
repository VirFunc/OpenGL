#include"Shader.h"
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
					<< "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
					<< "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
	}
}

bool Shader::build_from_memory(const char*v, const char* f)
{
	int vShader, fShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &v, NULL);
	glCompileShader(vShader);
	checkCompileErrors(vShader, "VERTEX");
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &f, NULL);
	glCompileShader(fShader);
	checkCompileErrors(fShader, "FRAGMENT");

	proID = glCreateProgram();
	glAttachShader(proID, vShader);
	glAttachShader(proID, fShader);
	glLinkProgram(proID);
	checkCompileErrors(proID, "PROGRAM");

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	return true;
}

Shader::~Shader()
{
	glDeleteProgram(proID);
}

Shader::Shader(const Shader &s)
{
	proID = s.proID;
}

bool Shader::build_from_file(const std::string vertexPath, const std::string fragmentPath)
{
	std::ifstream vShaderFile, fShaderFile;
	std::stringstream vShaderStream;
	std::stringstream fShaderStream;
	std::string vCodeStr, fCodeStr;
	//open file
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);
	if (!(vShaderFile.is_open() && fShaderFile.is_open()))
		return false;
	//get buffer
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();
	//get string
	vCodeStr = vShaderStream.str();
	fCodeStr = fShaderStream.str();

	if (vCodeStr.empty() || fCodeStr.empty())
		return false;
	//get code
	int vPos = vCodeStr.find("#", 0);
	int fPos = fCodeStr.find("#", 0);
	vCodeStr = vCodeStr.substr(vPos, vCodeStr.length());
	fCodeStr = fCodeStr.substr(fPos, fCodeStr.length());
	//get char ptr
	const char* vCodePtr = vCodeStr.c_str();
	const char* fCodePtr = fCodeStr.c_str();
	//build shader
	if (build_from_memory(vCodePtr, fCodePtr))
		return true;
	return false;

	return true;
}

void Shader::use()
{
	if (proID)
	{
		glUseProgram(proID);
	}
}

void Shader::set_bool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(proID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(proID, name.c_str()), value);
}

void Shader::set_float(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(proID, name.c_str()), value);
}

void Shader::set_mat4f(const std::string & name, float * value) const
{
	auto loc = glGetUniformLocation(proID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, value);
}
