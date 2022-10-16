#include "cShader.h"

cShader::cShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	m_nRendererID = CreateShader(ReadFile(vertex_shader), ReadFile(fragment_shader));
}

cShader::~cShader()
{
	auto it = m_umShaders.find(m_sName);

	if (it != m_umShaders.end())
		m_umShaders.erase(it);

	glDeleteShader(m_nRendererID);
}

cShader* cShader::Create(const std::string& shader_name, const std::string& filename)
{
	cShader* shader = Get(shader_name);

	if (shader)
		return shader;

	shader = new cShader(shader_name, filename);
	m_umShaders.insert(std::make_pair(shader_name, shader));

	return shader;
}

cShader* cShader::Get(const std::string& shader_name)
{
	auto it = m_umShaders.find(shader_name);

	if (it != m_umShaders.end())
		return it->second;

	return nullptr;
}

void cShader::Disable()
{
	for (auto& s : m_umShaders)
	{
		cShader* shader = s.second;
		delete shader;
	}

	m_umShaders.clear();
}

void cShader::Bind()
{
	glUseProgram(m_nRendererID);
}

void cShader::Unbind()
{
	glUseProgram(0);
}

unsigned int cShader::CreateShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int cShader::GetId() const
{
	return m_nRendererID;
}

unsigned int cShader::CompileShader(unsigned int type, const std::string& src)
{
	unsigned int id = glCreateShader(type);
	const char* source = src.c_str();

	glShaderSource(id, 1, &source, 0);
	glCompileShader(id);

	int ok;
	glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		
		char* msg = new char[length];
		glGetShaderInfoLog(id, length, &length, msg);
		std::cerr << SHADER_PREFIX << msg << '\n';

		delete[] msg;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

std::string cShader::ReadFile(const std::string& filename)
{
	std::ifstream t(filename);

	if (!t.is_open())
	{
		std::cerr << SHADER_PREFIX << "can't open a file\n";
		return "";
	}

	return std::string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

void cShader::UniformMatrix4f(const std::string& name, float* matrix, bool transpose)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniformMatrix4fv(loc, 1, (GLboolean)transpose, matrix);
}

void cShader::Uniform1i(const std::string& name, int x)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform1i(loc, x);
}

void cShader::Uniform1f(const std::string& name, float x)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform1f(loc, x);
}

void cShader::Uniform2i(const std::string& name, int x, int y)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform2i(loc, x, y);
}

void cShader::Uniform2f(const std::string& name, float x, float y)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform2f(loc, x, y);
}

void cShader::Uniform3i(const std::string& name, int x, int y, int z)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform3i(loc, x, y, z);
}

void cShader::Uniform3f(const std::string& name, float x, float y, float z)
{
	unsigned int loc = glGetUniformLocation(m_nRendererID, name.c_str());
	glUniform3f(loc, x, y, z);
}
