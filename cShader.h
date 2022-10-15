#pragma once

#include "GlfwSetup.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#define SHADER_PREFIX std::string("Shader: ")

class cShader
{
public:
	cShader(const std::string& vertex_shader, const std::string& fragment_shader);
	~cShader();

private:
	std::unordered_map<std::string, cShader*> m_umShaders;

	unsigned int m_nRendererID = -1;

public:
	std::string m_sName;

public:
	cShader* Create(const std::string& shader_name, const std::string& filename);
	cShader* Get(const std::string& shader_name);
	void Disable();

	void Delete();
	void Bind();
	void Unbind();

	unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
	unsigned int CompileShader(unsigned int type, const std::string& src);
	unsigned int GetId() const;

	std::string ReadFile(const std::string& filename);

};

