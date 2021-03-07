#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <memory>
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#include <string>
#include <vector>
#include "../Core/Debug.h"

struct Texture {
	GLuint ID;
	float width, height;
	std::string name;
	Texture();
};

class TextureHandler {
private:
	static std::vector<Texture*> textureList;

	static std::unique_ptr<TextureHandler> textureHandler;
	friend std::default_delete<TextureHandler>;
public:
	TextureHandler(const TextureHandler&) = delete;
	TextureHandler(TextureHandler&&) = delete;
	TextureHandler& operator=(const TextureHandler&) = delete;
	TextureHandler& operator=(TextureHandler&&) = delete;
	//Returns the Texture Handler instance
	static TextureHandler* GetInstance();
	//Creates a texture using the given name and file
	//PARAMS: _name: the texture name; textureFile: the filepath of the texture
	void CreateTexture(const std::string _name, const std::string textureFile);
	//Returns the ID of a texture
	//PARAMS: _name: the name of the texture to look for
	GLuint GetTextureID(const std::string _name) const;
	//Returns the struct of a texture
	//PARAMS: _name: the name of the texture to look for
	Texture* GetTextureData(const std::string _name) const;
	//Clears the texture list and resets the handler
	void OnDestroy();
private:
	TextureHandler();
	~TextureHandler();
};

#endif //TEXTUREHANDLER_H