#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glew.h>

class ShaderHandler {
private:
	static std::unordered_map<std::string, GLuint> shaderList;

	static std::unique_ptr<ShaderHandler> handlerInstance;
	friend std::default_delete<ShaderHandler>;
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;
	//Returns the pointer to the handler
	static ShaderHandler* GetInstance();
	//Creates a shader program using the given files
	//PARAMS: _name: the name to use for the program; vertFile: the vertex shader file; fragFile: the fragment shader file
	void CreateProgram(const std::string& _name, const std::string& vertFile, const std::string& fragFile);
	//Returns the ID of a program
	//PARAMS: _name: the name of the program to find
	GLuint GetShader(const std::string& _name) const;

	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();

	std::string ReadShader(const std::string& _filename);

	GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName_);
};

#endif //SHADERHANDLER_H