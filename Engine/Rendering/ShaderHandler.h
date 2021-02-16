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

	static ShaderHandler* GetInstance();

	void CreateProgram(const std::string& _name, const std::string& vertFile, const std::string& fragFile);

	GLuint GetShader(const std::string& _name) const;

	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();

	std::string ReadShader(const std::string& _filename);

	GLuint CreateShader(GLenum shaderType, const std::string& source, const std::string& shaderName_);
};

#endif //SHADERHANDLER_H