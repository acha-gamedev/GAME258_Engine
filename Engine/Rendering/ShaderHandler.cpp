#include "ShaderHandler.h"
#include "../Core/Debug.h"

std::unique_ptr<ShaderHandler> ShaderHandler::handlerInstance = nullptr;
std::unordered_map<std::string, GLuint> ShaderHandler::shaderList = std::unordered_map<std::string, GLuint>();

ShaderHandler::ShaderHandler() {}

ShaderHandler::~ShaderHandler() {
	OnDestroy();
}

void ShaderHandler::OnDestroy() {
	if (shaderList.size() > 0) {
		for (auto s : shaderList) {
			glDeleteShader(s.second);
		}
		shaderList.clear();
	}
}

ShaderHandler* ShaderHandler::GetInstance()
{
	if (handlerInstance.get() == nullptr) {
		handlerInstance.reset(new ShaderHandler);
	}
	return handlerInstance.get();
}

GLuint ShaderHandler::GetShader(const std::string& _name) const
{
	if (shaderList.find(_name) != shaderList.end()) {
		return shaderList[_name];
	}
	Debug::LogWarning("Shader " + _name + " not found", "Engine/Rendering/ShaderHandler.cpp", __LINE__);
	return 0;
}

void ShaderHandler::CreateProgram(const std::string& _name, const std::string& vertFile, const std::string& fragFile) {
	std::string vertShaderCode = ReadShader(vertFile);
	std::string fragShaderCode = ReadShader(fragFile);
	if (vertShaderCode == "" || fragShaderCode == "") {
		return;
	}

	GLuint vertShader = CreateShader(GL_VERTEX_SHADER, vertShaderCode, _name);
	GLuint fragShader = CreateShader(GL_FRAGMENT_SHADER, fragShaderCode, _name);
	if (vertShader == 0 || fragShader == 0) {
		return;
	}

	GLint linkResult; 
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (!linkResult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string logString(programLog.begin(), programLog.end());
		Debug::LogError("Failed to link shader " + _name + ". Error: " + logString, __FILE__, __LINE__);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		glDeleteProgram(program);
		return;
	}

	shaderList[_name] = program;
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

std::string ShaderHandler::ReadShader(const std::string& _filename) {
	std::string shader;
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	try {
		file.open(_filename);
		std::stringstream temp;
		temp << file.rdbuf();
		file.close();
		shader = temp.str();
	}
	catch (std::ifstream::failure error) {
		Debug::LogError("Could not read shader " + _filename, __FILE__, __LINE__);
		return "";
	}
	return shader;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType, const std::string& source, const std::string& _shaderName) {
	GLint result = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shaderCode = source.c_str();
	const int shaderSize = source.size();

	glShaderSource(shader, 1, &shaderCode, &shaderSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::string logString(shaderLog.begin(), shaderLog.end());
		Debug::LogError("Error compiling shader " + _shaderName + ". Error: " + logString, __FILE__, __LINE__);
		return 0;
	}

	return shader;
}