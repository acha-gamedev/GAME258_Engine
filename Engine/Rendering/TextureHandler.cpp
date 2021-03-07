#include "TextureHandler.h"

std::unique_ptr<TextureHandler> TextureHandler::textureHandler = nullptr;
std::vector<Texture*> TextureHandler::textureList = std::vector<Texture*>();

TextureHandler::TextureHandler() {}

TextureHandler::~TextureHandler() {
	OnDestroy();
}

TextureHandler* TextureHandler::GetInstance()
{
	if (textureHandler.get() == nullptr) {
		textureHandler.reset(new TextureHandler);
	}
	return textureHandler.get();
}

void TextureHandler::OnDestroy() {
	if (textureList.size() > 0) {
		for (auto t : textureList) {
			glDeleteTextures(sizeof(GLuint), &t->ID);
			delete t;
			t = nullptr;
		}
		textureList.clear();
	}
}

GLuint TextureHandler::GetTextureID(const std::string _name) const
{
	if (textureList.size() > 0) {
		for (auto t : textureList) {
			if (t->name == _name) {
				return t->ID;
			}
		}
	}
	return 0;
}

Texture* TextureHandler::GetTextureData(const std::string _name) const
{
	if (textureList.size() > 0) {
		for (auto t : textureList) {
			if (t->name == _name) {
				return t;
			}
		}
	}
	return nullptr;
}

void TextureHandler::CreateTexture(const std::string _name, const std::string textureFile) {
	if (GetTextureData(_name)) {
		return;
	}
	Texture* temp = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFile.c_str());
	if (surface == nullptr) {
		Debug::LogError("Surface for texture " + _name + "failed to create", "Engine/Rendering/TextureHandler.cpp", __LINE__);
		delete temp;
		temp = nullptr;
		return;
	}
	glGenTextures(1, &temp->ID);
	glBindTexture(GL_TEXTURE_2D, temp->ID);
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	temp->width = static_cast<float>(surface->w);
	temp->height = static_cast<float>(surface->h);
	temp->name = _name;
	textureList.push_back(temp);
	SDL_FreeSurface(surface);
	surface = nullptr;
}

Texture::Texture() : ID(0), width(0.0f), height(0.0f), name("") {}
