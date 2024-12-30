#include "Shader.h"
#include "Debug/Logger.h"
#include "fstream"

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	LOG_FUNC();

	std::string vertSourceStr = read_file_contents(vertexShaderFile);
	std::string fragSourceStr = read_file_contents(fragmentShaderFile);

	const char* vertexShaderSource = vertSourceStr.c_str();
	const char* fragmentShaderSource = fragSourceStr.c_str();

	// Compilation results
	int bSuccess;
	char info[512];
	
	// Create Vertex Shader, inject its source code and compile
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check Compilation Status
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, info);
		LOG(Warning, "Failed to compile vertex shader. INFO : {}", info);
	}
	else 
	{
		LOG(Log, "Compiled Vertex Shader Successfully.");
	}

	// Create Fragment Shader, inject its source code and compile
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check Compilation Status
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, info);
		LOG(Warning, "Failed to compile vertex shader. INFO : {}", info);
	}
	else
	{
		LOG(Log, "Compiled Vertex Shader Successfully.");
	}



	// Create Shader Program
	ID = glCreateProgram();

	// Attach Shaders to Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID,fragmentShader);

	// Link Program
	glLinkProgram(ID);

	// Check Linking Status
	glGetProgramiv(ID, GL_LINK_STATUS, &bSuccess);
	if (!bSuccess)
	{
		glGetProgramInfoLog(ID, 512, NULL, info);
		LOG(Warning, "Failed to link shaders for program. INFO : {}", info);
	}
	else
	{
		LOG(Log, "Linked Shaders to program Successfully.");
	}


	// Delete Shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate()
{
	//LOG_FUNC();

	glUseProgram(ID);
}

void Shader::cleanUp()
{
	LOG_FUNC();

	glDeleteProgram(ID);
}

std::string Shader::read_file_contents(const std::string& file)
{
	std::ifstream in(file, std::ios::binary);
	if (in) 
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	LOG(Error, "Could not get contents for file {}", file);
	return std::string();
}
